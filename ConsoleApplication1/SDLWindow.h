#pragma once

#include <SDL.h>
#include <string>

struct SDL_Renderer;
class SDLWindow
{
public:
	SDLWindow(const std::string& title, int x, int y, int w, int h, Uint32 flags = 0);
	SDLWindow(const SDLWindow&) = delete;
	SDLWindow(SDLWindow&& font) noexcept;
	~SDLWindow();

	/*SDLppRenderer CreateRenderer(Uint32 flags);
	SDLppRenderer CreateRenderer(int index, Uint32 flags);*/

	SDLWindow& operator=(const SDLWindow&) = delete;
	SDLWindow& operator=(SDLWindow&& font);

public:
	SDL_Window* m_window;
};