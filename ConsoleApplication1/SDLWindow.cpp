#include "SDLWindow.h"

SDLWindow::SDLWindow(const std::string& title, int x, int y, int w, int h, Uint32 flags)
{
	m_window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
}

SDLWindow::SDLWindow(SDLWindow&& window) noexcept
{
	m_window = window.m_window;
	window.m_window = nullptr;
}

SDLWindow::~SDLWindow()
{
	if (m_window)
		SDL_DestroyWindow(m_window);
}

//SDLppRenderer SDLWindow::CreateRenderer(Uint32 flags)
//{
//	return CreateRenderer(-1, flags);
//}


//SDLppRenderer SDLWindow::CreateRenderer(int index, Uint32 flags)
//{
//	SDL_Renderer* renderer = SDL_CreateRenderer(m_window, index, flags);
//	if (!renderer)
//		throw std::runtime_error(std::string("failed to create renderer: ") + SDL_GetError());
//
//	return SDLppRenderer(renderer);
//}

SDLWindow& SDLWindow::operator=(SDLWindow&& window)
{
	if (m_window)
		SDL_DestroyWindow(m_window);

	m_window = window.m_window;
	window.m_window = nullptr;

	return *this;
}
