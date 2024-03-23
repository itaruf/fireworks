#pragma once

#ifndef PARTICULE_H
#define PARTICULE_H

#include "Vector.h"
#include "Sprite.h"
#include "SDLRenderer.h"

#include <SDL_render.h>
#include <SDL_image.h>
#include <SDL.h>
#include <memory>

struct SDL_Renderer;
class Particule
{
public:
	Vector _position;
	Vector _force;
	std::shared_ptr<SDL_Renderer> _screenRenderer;
	std::shared_ptr<Sprite> sprite;
	int vie;
	int taille;
	int vieActuelle;
	const float GRAVITE = 980;

	Particule(std::shared_ptr<SDL_Renderer> renderer, std::string _modele, std::string _couleur, int vie, Vector& _position, Vector& _force, int taille, std::shared_ptr<Sprite>& sprite);
	~Particule();

	void Update(int deltaTime);
	void Render();
	bool EstVivante();
};

inline bool Particule::EstVivante()
{
	if (vie > vieActuelle)
		return true;
	return false;
}

#endif PARTICULE_H