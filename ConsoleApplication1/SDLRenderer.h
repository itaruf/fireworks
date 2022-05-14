#pragma once

#ifndef SDLRENDERER_H
#define SDLRENDERER_H

//#include "SDLTexture.hpp"
#include <SDL.h>
#include <string>

class SDLRenderer
{
public:
	SDLRenderer(const SDLRenderer&) = default;
	SDLRenderer(SDLRenderer&& renderer) noexcept;
	~SDLRenderer();

	SDLRenderer& operator=(const SDLRenderer&) = delete;
	SDLRenderer& operator=(SDLRenderer&& renderer) noexcept;

	SDL_Renderer* renderer;
	SDLRenderer(SDL_Renderer* other);
private:

};

#endif SDLRENDERER_H