#include "Particule.h"

Particule::Particule(SDL_Renderer* screenRenderer, std::string _modele, std::string _couleur, int vie, std::unique_ptr<Vector> _position, std::unique_ptr<Vector> _force, int taille, std::shared_ptr<Sprite>& sprite) 
	: vie{ vie * 1000 }, vieActuelle{ 0 }, _position{ _position.release() }, _force{ _force.release() }, taille{ taille }, sprite{sprite}
{
}

Particule::~Particule()
{
	/*std::cout << "PARTICULE DESTRUCTOR CALLED" << std::endl;*/
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

	newPosition = nullptr;
	/*delete newPosition;*/
	/*std::cout << _position << std::endl;
	std::cout << newPosition << std::endl;*/
}

void Particule::Render(SDLRenderer& screenRenderer)
{
	if (!screenRenderer.renderer)
		return;

	if (!_position)
		return;

	unsigned char alpha{ 0 };
	if (vie > vieActuelle)
		alpha = (255 * (vie - vieActuelle)) / vie;
	sprite.get()->Render(screenRenderer.renderer, _position->x, _position->y, taille, taille, alpha);
}
