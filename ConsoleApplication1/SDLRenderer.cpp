#include "SDLRenderer.h"

SDLRenderer::SDLRenderer(SDL_Renderer* renderer) : renderer(renderer)
{
}

SDLRenderer::SDLRenderer(SDLRenderer&& renderer) noexcept
{
	this->renderer = renderer.renderer;
	renderer.renderer = nullptr;
}

SDLRenderer::~SDLRenderer()
{
	std::cout << "SDL RENDERER DESTRUCTOR CALLED" << std::endl;
	if (this->renderer)
		SDL_DestroyRenderer(this->renderer);
}

SDLRenderer& SDLRenderer::operator=(SDLRenderer&& other) noexcept
{
	if (this == &other)
		return *this;

	if (this->renderer)
		SDL_DestroyRenderer(this->renderer);

	this->renderer = other.renderer;
	other.renderer = nullptr;

	return *this;
}
