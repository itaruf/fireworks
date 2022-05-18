#include "Particule.h"

Particule::Particule(std::shared_ptr<SDL_Renderer> screenRenderer, std::string _modele, std::string _couleur, int vie, Vector& _position, Vector& _force, int taille, std::shared_ptr<Sprite>& sprite) : _screenRenderer{ screenRenderer }, vie { vie * 1000 }, vieActuelle{ 0 }, _position{ _position }, _force{ _force }, taille{ taille }, sprite{ sprite }
{
}

Particule::~Particule()
{
	/*std::cout << "PARTICULE DESTRUCTOR CALLED" << std::endl;*/
}

void Particule::Update(int deltaTime)
{
	vieActuelle += deltaTime;
	Vector pos{_position.x + _force.x * deltaTime / 1000, _position.y + _force.y * deltaTime / 1000};

	//gravité
	_force.y += deltaTime * GRAVITE / 1000;

	//rebond
	if (pos.y + taille / 2 >= 720)
	{
		pos.y = 720 - (pos.y - 720);
		_force.y *= - 0.8f;
	}
	_position.x = pos.x;
	_position.y = pos.y;
}

void Particule::Render()
{
	if (!_screenRenderer)
		return;

	unsigned char alpha{ 0 };
	if (vie > vieActuelle)
		alpha = (255 * (vie - vieActuelle)) / vie;
	sprite.get()->Render(_screenRenderer, _position.x, _position.y, taille, taille, alpha);
}
