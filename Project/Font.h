#pragma once

#ifndef FONT_H
#define FONT_H

#include <SDL_ttf.h>
#include <string>
#include <iostream>

class Font
{
public:
	TTF_Font* _font;

	Font() = delete;
	Font(std::string name, int size);
	Font(const Font& font) = delete;
	Font(Font&& moved) = delete;
	~Font();
	Font& operator=(const Font&) = delete;

	SDL_Texture* CreateTextTexture(std::string text, SDL_Color& color, SDL_Renderer* renderer);

};

#endif FONT_H
