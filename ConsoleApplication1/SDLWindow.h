#pragma once

#include <SDL.h>
#include <string>
#include <iostream>

struct SDL_Renderer;
class SDLWindow
{
public:
	SDLWindow(std::string&& title, int x, int y, int w, int h, Uint32 flags = 0);
	SDLWindow(const SDLWindow&) = delete;
	SDLWindow(SDLWindow&&) = delete;
	SDLWindow& operator=(const SDLWindow&) = delete;
	SDLWindow& operator=(SDLWindow&&) = delete;
	~SDLWindow();

	/*SDLppRenderer CreateRenderer(Uint32 flags);
	SDLppRenderer CreateRenderer(int index, Uint32 flags);*/
public:
	SDL_Window* window;
};