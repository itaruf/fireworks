#pragma once

#ifndef PARTICULE_H
#define PARTICULE_H

#include <SDL_image.h>

#include "Vector.h"
#include "Sprite.h"
#include "SDLRenderer.h"
#include <memory>

class Particule
{
public:
	std::unique_ptr<Vector> _position;
	std::unique_ptr<Vector> _force;
	std::shared_ptr<Sprite> sprite;
	int vie;
	int taille;
	int vieActuelle;
	const float GRAVITE = 980;

	Particule(SDL_Renderer* renderer, std::string _modele, std::string _couleur, int vie, std::unique_ptr<Vector> _position, std::unique_ptr<Vector> _force, int taille, std::shared_ptr<Sprite>& sprite);
	~Particule();

	void Update(int deltaTime);
	void Render(SDLRenderer& screenRenderer);
	bool EstVivante();
};

inline bool Particule::EstVivante()
{
	if (vie > vieActuelle)
		return true;
	return false;
}

#endif PARTICULE_H