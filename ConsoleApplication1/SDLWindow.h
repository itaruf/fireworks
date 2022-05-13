#pragma once

#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <SDL.h>
#include <string>
#include <iostream>
#include "SDLRenderer.h"

class SDLWindow
{
public:
	SDLWindow(std::string&& title, int x, int y, int w, int h, Uint32 flags = 0);
	SDLWindow(const SDLWindow&) = delete;
	SDLWindow(SDLWindow&&) = delete;
	SDLWindow& operator=(const SDLWindow&) = delete;
	SDLWindow& operator=(SDLWindow&&) = delete;
	~SDLWindow();

	SDLRenderer CreateRenderer(Uint32 flags);
	SDLRenderer CreateRenderer(int index, Uint32 flags);
public:
	SDL_Window* window;
};

#endif SDLWINDOW_H