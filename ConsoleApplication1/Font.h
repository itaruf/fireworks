#pragma once
#include <SDL_ttf.h>
#include <string>
class Font
{
	TTF_Font* _font;
public:
	Font() = delete;
	Font(std::string name, int size);
	Font(const Font& font) = delete;
	Font(Font&& moved) = delete;
	~Font();
	Font& operator=(const Font&) = delete;

	SDL_Texture* CreateTextTexture(std::string text, SDL_Color color, SDL_Renderer* renderer);

};

