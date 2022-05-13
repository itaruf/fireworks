#include "GenerateurParticule.h"

GenerateurParticule::~GenerateurParticule()
{
	std::cout << "GENERATOR DESTRUCTOR CALLED" << std::endl;
	/*std::cout << _liste.size() << std::endl;*/

	for (const auto& particule : _liste)
		delete particule;
	delete _position;
}

GenerateurParticule::GenerateurParticule(SDL_Renderer* screenRenderer, int nbParticulesDebut, int nbParticulesMax, int nbParticulesTotal, std::string modele, std::string couleur, int vieMin, int vieMax, Vector* position, int tailleMin, int tailleMax, int force, int angleMax)
	: _screenRenderer{ screenRenderer }, _nbParticulesMax{ nbParticulesMax }, _nbParticulesRestantes{ nbParticulesTotal }, _modele{ std::move(modele) }, _couleur{ std::move(couleur) }, _vieMin{vieMin}, _vieMax{vieMax}, _position{position}, _tailleMin{tailleMin}, _tailleMax{tailleMax}, _force{force}, _angleMax{angleMax}
{

	std::cout << "GENERATEUR CONSTRUCTOR CALLED" << std::endl;

	/*std::cout << screenRenderer << std::endl;
	std::cout << _screenRenderer << std::endl;*/

	_liste.reserve(_nbParticulesRestantes);

	/*std::cout << _nbParticulesMax << std::endl;
	std::cout << _liste.capacity() << std::endl;*/

	for (int i = 0; i < nbParticulesDebut; ++i)
	{
		AjouterParticule();
	}
}

void GenerateurParticule::AjouterParticule()
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

	//auto tmp = new Particule(_screenRenderer, _modele, _couleur, vie, new Vector(_position->x, _position->y), new Vector(-_force * sin(angle), _force * cos(angle)), taille);
	_liste.emplace_back(new Particule(_screenRenderer, _modele, _couleur, vie, new Vector(_position->x, _position->y), new Vector(-_force * sin(angle), _force * cos(angle)), taille));
	/*std::cout << _liste.size() << std::endl;*/
	//tmp = nullptr;
	_nbParticulesRestantes--;
}

void GenerateurParticule::Update(int deltaTime)
{
	for (auto particule : _liste)
	{
		if (particule)
		{
			particule->Update(deltaTime);
			if (!particule->EstVivante())
			{
				_liste.erase(std::find(_liste.begin(), _liste.end(), particule));
				delete particule;
				if (GetNbParticulesActives() < _nbParticulesRestantes && EstActif())
					AjouterParticule();
			}
		}
	}
}

int GenerateurParticule::GetNbParticulesActives()
{
	int nb{ 0 };
	for (const auto& particule : _liste)
		if (particule)
			nb++;

	return nb;
}

void GenerateurParticule::Render(SDL_Renderer* screenRenderer)
{
	for (const auto& particule : _liste)
		if (particule)
			particule->Render(screenRenderer);
}

Particule* GenerateurParticule::GetPooledParticule()
{
	return nullptr;
}
