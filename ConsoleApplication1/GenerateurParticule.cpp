#include "GenerateurParticule.h"

GenerateurParticule::~GenerateurParticule()
{
	std::cout << "GENERATOR DESTRUCTOR CALLED" << std::endl;

	for (auto particule : _particles)
		delete particule;
	_particles.clear();

	/*std::cout << _particles.size() << std::endl;*/
}

GenerateurParticule::GenerateurParticule(SDL_Renderer* screenRenderer, int nbParticulesDebut, int nbParticulesMax, int nbParticulesTotal, std::string modele, std::string couleur, int vieMin, int vieMax, std::unique_ptr<Vector> position, int tailleMin, int tailleMax, int force, int angleMax)
	: _screenRenderer{ screenRenderer }, _nbParticulesDebut{ nbParticulesDebut == 0 ? ++nbParticulesDebut : nbParticulesDebut},  _nbParticulesMax{ nbParticulesMax > nbParticulesTotal ? nbParticulesTotal : nbParticulesMax }, _nbParticulesRestantes{ nbParticulesTotal }, _modele{ std::move(modele) }, _couleur{ std::move(couleur) }, _vieMin{ vieMin }, _vieMax{ vieMax }, _position{ position.release() }, _tailleMin{ tailleMin }, _tailleMax{ tailleMax }, _force{ force }, _angleMax{ angleMax }
{
	std::cout << "GENERATEUR CONSTRUCTOR CALLED" << std::endl;
	_particles.reserve(_nbParticulesMax);

	/*std::cout << _nbParticulesDebut << std::endl;
	std::cout << _nbParticulesMax << std::endl;*/

	SDL_Surface* loadedSurface{ IMG_Load(("fireworks/" + _modele + "-" + _couleur + ".png").c_str()) };	

	if (!loadedSurface)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", ("fireworks/" + _modele + "-" + _couleur + ".png").c_str(), IMG_GetError());
	}

	//Create texture from surface pixels
	else
	{
		this->sprite = std::make_shared<Sprite>(SDL_CreateTextureFromSurface(screenRenderer, loadedSurface));
		std::cout << sprite.get()->GetHeight() << std::endl;
		std::cout << sprite.use_count() << std::endl;

		if (!sprite->GetSprite())
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", ("fireworks/" + _modele + "-" + _couleur + ".png").c_str(), SDL_GetError());
		}
	}

	/*Get rid of old loaded surface*/
	SDL_FreeSurface(loadedSurface);

	for (int i = 0; i < nbParticulesDebut; ++i)
		AjouterParticule(i);

	std::cout << _particles.size() << std::endl;
	std::cout << _nbParticulesRestantes << std::endl;

}

void GenerateurParticule::AjouterParticule(int i)
{
	int angle{ 0 };
	if (_angleMax != 0)
		angle = rand() % _angleMax;
	if (rand() % 2 == 1)
		angle = -angle;
	int vie{ _vieMin };
	if (_vieMin != _vieMax)
		vie = _vieMin + rand() % (_vieMax - _vieMin);
	int taille{ _tailleMin };
	if (_tailleMin != _tailleMax)
		taille = _tailleMin + rand() % (_tailleMax - _tailleMin);

	/*if (_particles[i])
		delete _particles[i];*/

	_particles.emplace_back(new Particule(_screenRenderer, _modele, _couleur, vie, std::make_unique<Vector>(_position->x, _position->y), std::make_unique<Vector>(-_force * sin(angle), _force * cos(angle)), taille, sprite));
	std::cout << sprite.use_count() << std::endl;
}

void GenerateurParticule::Update(int deltaTime)
{
	std::cout << "restant: " << _nbParticulesRestantes << std::endl;
	std::cout << "actif: " << GetNbParticulesActives() << std::endl;
	std::cout << EstActif() << std::endl;

	for (int i = 0; i < _nbParticulesMax; ++i)
	{
		if (_particles.size() < i + 1)
		{
			if (GetNbParticulesActives() < _nbParticulesRestantes && EstActif())
			{
				_nbParticulesRestantes--;
				AjouterParticule(0);
			}
		}

		/*if (!_particles[i])
		{
			auto tmp = _particles[i];
			_particles.erase(std::find(_particles.begin(), _particles.end(), _particles[i]));
			delete tmp;
			_nbParticulesRestantes--;
			if (GetNbParticulesActives() < _nbParticulesRestantes && EstActif())
				AjouterParticule(0);
		}*/

		else if (!_particles[i]->EstVivante())
		{
			auto tmp = _particles[i];
			_particles.erase(std::find(_particles.begin(), _particles.end(), _particles[i]));
			delete tmp;
			_nbParticulesRestantes--;
			if (GetNbParticulesActives() < _nbParticulesRestantes && EstActif())
				AjouterParticule(0);
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

void GenerateurParticule::Render(SDLRenderer& screenRenderer)
{
	for (const auto& particule : _particles)
		if (particule)
			particule->Render(screenRenderer);
}

Particule* GenerateurParticule::GetPooledParticule()
{
	return nullptr;
}
