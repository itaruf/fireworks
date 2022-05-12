#include "Sprite.h"
#include <SDL.h>

Sprite::Sprite(SDL_Texture* spriteImage): _spriteImage(spriteImage)
{
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(_spriteImage);
}

void Sprite::Render(SDL_Renderer* screenRenderer, int posX, int posY, int width, int height, unsigned char alpha)
{
    if (screenRenderer == nullptr)
    {
        delete screenRenderer;
        return;
    }

    if (_spriteImage == nullptr)
        return;

    SDL_SetTextureAlphaMod(_spriteImage, alpha);
    SDL_Rect rect = { posX - (width / 2), posY - (height / 2), width, height };
    SDL_RenderCopy(screenRenderer, _spriteImage, NULL, &rect);
}

int Sprite::GetWidth() const
{
    int width, height;
    SDL_QueryTexture(_spriteImage, NULL, NULL, &width, &height);
    return width;
}

int Sprite::GetHeight() const
{
    int width, height;
    SDL_QueryTexture(_spriteImage, NULL, NULL, &width, &height);
    return height;
}
