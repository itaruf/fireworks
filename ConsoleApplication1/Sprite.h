#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL_surface.h>
#include <SDL_render.h>
#include <SDL.h>

#include <iostream>
#include <string>

struct SDL_Texture;
class Sprite
{
protected:
	SDL_Texture* _spriteImage{ nullptr };
public:
	Sprite() = delete;
	Sprite(SDL_Texture* _spriteImage);
	Sprite(const Sprite&) = delete;
	Sprite(Sprite*&& sprite) noexcept;
	Sprite& operator=(const Sprite&) = delete;
	Sprite& operator=(Sprite&& sprite) noexcept;
	~Sprite();

	void Render(SDL_Renderer* screenRenderer, int posX, int posY, int width, int height, unsigned char alpha);

	int GetWidth() const;
	int GetHeight() const;
	SDL_Texture* GetSprite();
	void SetSprite(SDL_Texture* sprite);

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
inline SDL_Texture* Sprite::GetSprite()
{
	if (_spriteImage)
		return _spriteImage;
	return nullptr;
}

#endif SPRITE_H