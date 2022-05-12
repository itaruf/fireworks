#pragma once
#include <string>
#include <SDL_surface.h>
#include <SDL_render.h>

class Sprite
{
protected:
	SDL_Texture* _spriteImage = nullptr;
public:
	Sprite() = delete;
	Sprite(SDL_Texture* _spriteImage);
	Sprite(const Sprite&) = delete;
	Sprite(Sprite&&) = delete;
	Sprite& operator=(const Sprite&) = delete;
	~Sprite();

	void Render(SDL_Renderer* screenRenderer, int posX, int posY, int width, int height, unsigned char alpha);

	int GetWidth() const;
	int GetHeight() const;
};