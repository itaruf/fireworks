#pragma once

#ifndef SDLTEXTURE_H
#define SDLTEXTURE_H

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

#include "SDLRenderer.h"
#include "Font.h"

class SDLTexture
{
public:
	SDLTexture(SDL_Texture* texture);
	SDLTexture(const SDLTexture&) = delete;
	SDLTexture(SDLTexture&& texture) noexcept;
	~SDLTexture();

	SDLTexture& operator=(const SDLTexture&) = delete;
	SDLTexture& operator=(SDLTexture&& texture);

	static SDLTexture FromSurface(const SDLRenderer& renderer, std::string message, SDL_Color& color);

	SDL_Texture* _texture;
};

#endif SDLTEXTURE_H