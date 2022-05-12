#include "Particule.h"
#include <SDL_image.h>
#include <iostream>

Particule::Particule(SDL_Renderer* renderer, std::string _modele, std::string _couleur, int vie, Vector* _position, Vector* _force, int taille) 
	: vie{ vie * 1000 }, vieActuelle{ 0 }, _position{ _position }, _force{ _force }, taille{ taille }
{
	/*std::cout << "Particule Constructor called" << std::endl;*/

	//Load image at specified path
	SDL_Texture* spriteImage{ nullptr };
	SDL_Surface* loadedSurface{ IMG_Load(("fireworks/" + _modele + "-" + _couleur + ".png").c_str()) };

	if (!loadedSurface)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", ("fireworks/" + _modele + "-" + _couleur + ".png").c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		spriteImage = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (!spriteImage)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", ("fireworks/" + _modele + "-" + _couleur + ".png").c_str(), SDL_GetError());
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	sprite = new Sprite(spriteImage);
	spriteImage = nullptr;

	/*sprite->SetSprite(spriteImage);*/

	/*std::cout << spriteImage << std::endl;*/
}

// Move assignment constructor
Particule& Particule::operator=(Particule*&& other) noexcept
{
	std::cout << "Particule Move Constructor Assignement called" << std::endl;

	/*if (this != other)
	{
		delete sprite;
		delete _force;
		delete _position;

		this->sprite = other->sprite;
		this->vie = other->vie * 1000;
		this->vieActuelle = other->vieActuelle;
		this->_position = other->_position;
		this->_force = other->_force;
		this->taille = other->taille;

		other->_position = nullptr;
	}*/

	return *this;
}

Particule::~Particule()
{
	/*std::cout << "Particule Deleter" << std::endl;*/
	delete sprite;
	delete _force;
	delete _position;
}

void Particule::Update(int deltaTime)
{
	if (!_position)
		return;

	vieActuelle += deltaTime;
	Vector* newPosition{ new Vector(_position->x + _force->x * deltaTime / 1000, _position->y + _force->y * deltaTime / 1000)};

	//gravité
	_force->y += deltaTime * GRAVITE / 1000;

	//rebond
	if (newPosition->y + taille / 2 >= 720)
	{
		newPosition->y = 720 - (newPosition->y - 720);
		_force->y *= - 0.8;
	}
	_position->x = newPosition->x;
	_position->y = newPosition->y;

	newPosition = nullptr;
}

void Particule::Render(SDL_Renderer* screenRenderer)
{
	if (!screenRenderer)
		return;

	unsigned char alpha{ 0 };
	if (vie > vieActuelle)
		alpha = (255 * (vie - vieActuelle)) / vie;
	sprite->Render(screenRenderer, _position->x, _position->y, taille, taille, alpha);
}

bool Particule::EstVivante()
{
	if (vie > vieActuelle)
		return true;
	return false;
}
