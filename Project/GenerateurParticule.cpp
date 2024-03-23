#include "GenerateurParticule.h"

GenerateurParticule::~GenerateurParticule()
{
	/*std::cout << "GENERATOR DESTRUCTOR CALLED" << std::endl;*/
	for (auto& particule : _particles)
		delete particule;
	_particles.clear();
}

GenerateurParticule::GenerateurParticule(std::shared_ptr<SDL_Renderer> screenRenderer, int nbParticulesDebut, int nbParticulesMax, int nbParticulesRestantes, std::string modele, std::string couleur, int vieMin, int vieMax, Vector& position, int tailleMin, int tailleMax, int force, int angleMax)
	: _screenRenderer{ screenRenderer }, _nbParticulesDebut{ nbParticulesDebut == 0 ? nbParticulesDebut++ : nbParticulesDebut},  _nbParticulesMax{ nbParticulesMax > nbParticulesRestantes ? nbParticulesRestantes : nbParticulesMax }, _nbParticulesRestantes{ nbParticulesRestantes }, _modele{ std::move(modele) }, _couleur{ std::move(couleur) }, _vieMin{ vieMin }, _vieMax{ vieMax }, _position{ position }, _tailleMin{ tailleMin }, _tailleMax{ tailleMax }, _force{ force }, _angleMax{ angleMax }
{
	/*std::cout << "GENERATEUR CONSTRUCTOR CALLED" << std::endl;*/
	_particles.reserve(_nbParticulesMax);

	SDL_Surface* loadedSurface{ IMG_Load(("fireworks/" + _modele + "-" + _couleur + ".png").c_str()) };	

	if (!loadedSurface)
		printf("Unable to load image %s! SDL_image Error: %s\n", ("fireworks/" + _modele + "-" + _couleur + ".png").c_str(), IMG_GetError());

	//Create texture from surface pixels
	else
	{
		_sprite = std::make_shared<Sprite>(SDL_CreateTextureFromSurface(screenRenderer.get(), loadedSurface));
		if (!_sprite)
			printf("Unable to create texture from %s! SDL Error: %s\n", ("fireworks/" + _modele + "-" + _couleur + ".png").c_str(), SDL_GetError());
	}

	/*Get rid of old loaded surface*/
	SDL_FreeSurface(loadedSurface);

	for (int i = 0; i < _nbParticulesDebut; ++i)
		AjouterParticule();
}

void GenerateurParticule::AjouterParticule()
{
	std::random_device myRandomDevice;
	unsigned seed = myRandomDevice();
	std::default_random_engine myRandomEngine(seed);

	int angle{ 0 };
	if (_angleMax != 0)
		angle = myRandomEngine() % _angleMax;
	if (myRandomEngine() % 2 == 1)
		angle = -angle;
	int vie{ _vieMin };
	if (_vieMin != _vieMax)
		vie = _vieMin + myRandomEngine() % (_vieMax - _vieMin);
	int taille{ _tailleMin };
	if (_tailleMin != _tailleMax)
		taille = _tailleMin + myRandomEngine() % (_tailleMax - _tailleMin);

	Vector pos{ _position.x, _position.y };
	Vector force{ static_cast<int>( -_force * sin(angle)), static_cast<int>(_force * cos(angle)) };

	_particles.emplace_back(new Particule(_screenRenderer, _modele, _couleur, vie, pos, force, taille, _sprite));
	_nbParticulesRestantes--;
}

void GenerateurParticule::Update(int deltaTime)
{
	for (int i = 0; i < _nbParticulesMax; ++i)
	{
		if ((int)_particles.size() <= i)
		{
			if (GetNbParticulesActives() < _nbParticulesRestantes && EstActif())
				AjouterParticule();
		}
		else if (!_particles[i]->EstVivante())
		{
			auto tmp = _particles[i];
			_particles.erase(std::find(_particles.begin(), _particles.end(), _particles[i]));
			delete tmp;
			if (GetNbParticulesActives() < _nbParticulesRestantes && EstActif())
				AjouterParticule();
		}
		else
			_particles[i]->Update(deltaTime);
	}
}

int GenerateurParticule::GetNbParticulesActives()
{
	int nb{ 0 };
	for (const auto& particule : _particles)
		if (particule)
			nb++;
	return nb;
}

void GenerateurParticule::Render()
{
	for (const auto& particule : _particles)
		if (particule)
			particule->Render();
}