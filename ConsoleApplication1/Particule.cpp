#include "Particule.h"

Particule::Particule(SDL_Renderer* screenRenderer, std::string _modele, std::string _couleur, int vie, Vector* _position, Vector* _force, int taille) 
	: vie{ vie * 1000 }, vieActuelle{ 0 }, _position{ _position }, _force{ _force }, taille{ taille }
{
	/*std::cout << "Particule Constructor called" << std::endl;*/

	std::cout << screenRenderer << std::endl;

	//Load image at specified path
	SDL_Surface* loadedSurface{ IMG_Load(("fireworks/" + _modele + "-" + _couleur + ".png").c_str()) };		

	if (!loadedSurface)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", ("fireworks/" + _modele + "-" + _couleur + ".png").c_str(), IMG_GetError());
	}

	//Create texture from surface pixels
	else 
	{
		sprite = new Sprite(SDL_CreateTextureFromSurface(screenRenderer, loadedSurface));
		if (!sprite->GetSprite())
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", ("fireworks/" + _modele + "-" + _couleur + ".png").c_str(), SDL_GetError());
		}
	}
	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
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
	/*std::cout << "PARTICULE DESTRUCTOR CALLED" << std::endl;*/
	delete sprite;
	delete _force;
	delete _position;
}

void Particule::Update(int deltaTime)
{
	if (!_position)
		return;

	if (!_force)
		return;

	vieActuelle += deltaTime;
	Vector* newPosition{ new Vector(_position->x + _force->x * deltaTime / 1000, _position->y + _force->y * deltaTime / 1000)};

	//gravité
	_force->y += deltaTime * GRAVITE / 1000;

	//rebond
	if (newPosition->y + taille / 2 >= 720)
	{
		newPosition->y = 720 - (newPosition->y - 720);
		_force->y *= - 0.8f;
	}
	_position->x = newPosition->x;
	_position->y = newPosition->y;

	/*newPosition = nullptr;*/
	delete newPosition;
	/*std::cout << _position << std::endl;
	std::cout << newPosition << std::endl;*/
}

void Particule::Render(SDL_Renderer* screenRenderer)
{
	if (!screenRenderer)
		return;

	if (!_position)
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
