#include "Font.h"

Font::Font(std::string name, int size)
{
	_font = TTF_OpenFont(name.c_str(), size);
	if (!_font) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}
}

Font::~Font()
{
	TTF_CloseFont(_font);
}

SDL_Texture* Font::CreateTextTexture(std::string text, SDL_Color color, SDL_Renderer* renderer)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended_Wrapped(_font, text.c_str(), color, 255);
	auto texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
	return texture;
}
