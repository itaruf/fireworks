#include "SDLTexture.h"

SDLTexture::SDLTexture(SDL_Texture* texture) : _texture(texture)
{
}

SDLTexture::SDLTexture(SDLTexture&& texture) noexcept
{
	_texture = texture._texture;
	texture._texture = nullptr;
}

SDLTexture::~SDLTexture()
{
	if (_texture)
		SDL_DestroyTexture(_texture);
}

SDLTexture& SDLTexture::operator=(SDLTexture&& other) noexcept
{
	/*std::cout << "MOVE ASSIGNMENT OPERATOR CALLLED" << std::endl;*/

	if (this == &other)
		return *this;

	if (_texture)
		SDL_DestroyTexture(_texture);

	_texture = other._texture;
	other._texture = nullptr;

	return *this;
}

SDLTexture SDLTexture::FromSurface(std::shared_ptr<SDL_Renderer> renderer, std::string message, SDL_Color& color)
{
	Font* font{ new Font("arial.ttf", 16) };

	SDL_Surface* surfaceMessage{ TTF_RenderText_Blended_Wrapped(font->_font, std::move(message.c_str()), color, 255) };
	SDL_Texture* texture{ SDL_CreateTextureFromSurface(renderer.get(), surfaceMessage) };

	/*std::cout << texture << std::endl;*/

	if (!texture)
		throw std::runtime_error(std::string("failed to create texture from surface: ") + SDL_GetError());

	delete font;
	SDL_FreeSurface(surfaceMessage);
	return SDLTexture(texture);
}
