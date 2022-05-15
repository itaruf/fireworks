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
	: _screenRenderer{ screenRenderer }, _nbParticulesDebut{ nbParticulesDebut == 0 ? ++nbParticulesDebut : nbParticulesDebut},  _nbParticulesMax{ nbParticulesMax > nbParticulesTotal ? nbParticulesTotal : nbParticulesMax }, _nbParticulesRestantes{ 200 }, _modele{ std::move(modele) }, _couleur{ std::move(couleur) }, _vieMin{ vieMin }, _vieMax{ vieMax }, _position{ position.release() }, _tailleMin{ tailleMin }, _tailleMax{ tailleMax }, _force{ force }, _angleMax{ angleMax }
{
	std::cout << "GENERATEUR CONSTRUCTOR CALLED" << std::endl;
	_particles.reserve(_nbParticulesMax);

	/*std::cout << _nbParticulesDebut << std::endl;
	std::cout << _nbParticulesMax << std::endl;*/

	for (int i = 0; i < 200; ++i)
	{
		_particles.emplace_back(nullptr);
	}

	for (int i = 0; i <10; ++i)
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

	if (_particles[i])
		delete _particles[i];

	_particles[i] = new Particule(_screenRenderer, _modele, _couleur, vie, std::make_unique<Vector>(_position->x, _position->y), std::make_unique<Vector>(-_force * sin(angle), _force * cos(angle)), taille);
}

void GenerateurParticule::Update(int deltaTime)
{
	/*std::cout << "restant: " << _nbParticulesRestantes << std::endl;
	std::cout << "actif: " << GetNbParticulesActives() << std::endl;
	std::cout << EstActif() << std::endl;*/

	for (int i = 0; i < 25; ++i)
	{
		if (!_particles[i])
		{
			if (GetNbParticulesActives() < _nbParticulesRestantes && EstActif())
				AjouterParticule(i);
		}
		else if (!_particles[i]->EstVivante())
		{
			_nbParticulesRestantes--;
			if (GetNbParticulesActives() < _nbParticulesRestantes && EstActif())
				AjouterParticule(i);
		}
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
