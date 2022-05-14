#pragma once

#ifndef PARTICULE_H
#define PARTICULE_H

#include <SDL_image.h>

#include "Vector.h"
#include "Sprite.h"
#include "SDLRenderer.h"

class Particule
{
public:
	Vector* _position;
	Vector* _force;

	Sprite* sprite{ nullptr };
	int vie;
	int taille;

	int vieActuelle;

	const float GRAVITE = 980;

	Particule(SDL_Renderer* renderer, std::string _modele, std::string _couleur, int vie, Vector* _position, Vector* _force, int taille);
	Particule& operator=(Particule*&& other) noexcept;
	
	~Particule();

	void Update(int deltaTime);

	void Render(SDLRenderer& screenRenderer);

	bool EstVivante();
};

#endif PARTICULE_H