#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL_surface.h>
#include <SDL_render.h>
#include <SDL.h>
#include <iostream>

struct SDL_Texture;
struct SDL_Renderer;
class Sprite
{
protected:
	SDL_Texture* _spriteImage;
public:
	Sprite() = delete;
	Sprite(SDL_Texture* _spriteImage);
	Sprite(const Sprite&) = delete;
	Sprite(Sprite*&& sprite) = delete;
	Sprite& operator=(Sprite&& sprite) = delete;
	Sprite& operator=(const Sprite&) = delete;
	~Sprite();

	void Render(std::shared_ptr<SDL_Renderer> screenRenderer, int posX, int posY, int width, int height, unsigned char alpha);

	int GetWidth() const;
	int GetHeight() const;
};

inline int Sprite::GetWidth() const
{
	if (!_spriteImage)
		return 0;

	int width, height;
	SDL_QueryTexture(_spriteImage, NULL, NULL, &width, &height);
	return width;
}

inline int Sprite::GetHeight() const
{
	if (!_spriteImage)
		return 0;

	int width, height;
	SDL_QueryTexture(_spriteImage, NULL, NULL, &width, &height);
	return height;
}

#endif SPRITE_H