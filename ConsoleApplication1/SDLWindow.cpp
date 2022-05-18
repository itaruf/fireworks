#include "SDLWindow.h"

SDLWindow::SDLWindow(std::string&& title, int x, int y, int w, int h, Uint32 flags)
{
	window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
}

SDLWindow::~SDLWindow()
{
	std::cout << "Window Destructor Called" << std::endl;
	if (window)
		SDL_DestroyWindow(window);
}

SDLRenderer SDLWindow::CreateRenderer(Uint32 flags)
{
	return CreateRenderer(-1, flags);
}


SDLRenderer SDLWindow::CreateRenderer(int index, Uint32 flags)
{
	SDL_Renderer* renderer = SDL_CreateRenderer(window, index, flags);
	return SDLRenderer(renderer);
}
