#pragma once

#ifndef GENERATEUR_PARTICULE_H
#define GENERATEUR_PARTICULE_H

#include "Particule.h"

#include <vector>
#include <iterator>
#include <algorithm>
#include "SDLRenderer.h"
#include <memory>

class GenerateurParticule
{
public:
	std::vector<Particule*> _particles;
	int _nbParticulesMax;
	int _nbParticulesRestantes;
	int _nbParticulesDebut;
	std::string _modele;
	std::string _couleur;
	SDL_Renderer* _screenRenderer;
	int _vieMin;
	int _vieMax;
	Vector _position;
	int _tailleMin;
	int _tailleMax;
	int _force;
	int _angleMax;
	std::shared_ptr<Sprite> sprite{ nullptr };

	~GenerateurParticule();
	GenerateurParticule(SDL_Renderer* screenRenderer, int nbParticulesDebut, int nbParticulesMax, int nbParticulesTotal, std::string modele, std::string couleur,
		int vieMin, int vieMax, Vector& position, int tailleMin, int tailleMax, int force, int angleMax);

	bool EstActif();
	void AjouterParticule();
	void Update(int deltaTime);
	int GetNbParticulesActives();
	void Render(SDLRenderer& screenRenderer);
};

inline bool GenerateurParticule::EstActif()
{
	if (_nbParticulesRestantes > 0)
		return true;
	return false;
}

#endif GENERATEUR_PARTICULE_H
