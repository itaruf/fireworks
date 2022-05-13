#include "Sprite.h"

Sprite::Sprite(SDL_Texture* spriteImage): _spriteImage(spriteImage)
{
    /*std::cout << "DEFAULT CONSTRUCTOR CALLED" << std::endl;*/
    /*spriteImage = nullptr;
    delete spriteImage;*/
   /* std::cout << std::addressof(spriteImage) << std::endl;
    std::cout << std::addressof(_spriteImage) << std::endl;*/
}

Sprite::Sprite(Sprite*&& sprite) noexcept
{
    std::cout << "SPRITE MOVE CONSTRUCTOR CALLED" << std::endl;
    _spriteImage = sprite->_spriteImage;
    delete sprite->_spriteImage;
}


Sprite& Sprite::operator=(Sprite&& other) noexcept
{
    std::cout << "SPRITE MOVE ASSIGMENT OPERATOR CALLED" << std::endl;

    if (this == &other)
        return *this;

    delete _spriteImage;

    _spriteImage = other._spriteImage;
    other._spriteImage = nullptr;

    return *this;

}
Sprite::~Sprite()
{
     SDL_DestroyTexture(_spriteImage);
}

void Sprite::Render(SDL_Renderer* screenRenderer, int posX, int posY, int width, int height, unsigned char alpha)
{
    if (!screenRenderer)
        return;

    if (!_spriteImage)
        return;

    SDL_SetTextureAlphaMod(_spriteImage, alpha);
    SDL_Rect rect{ posX - (width / 2), posY - (height / 2), width, height };
    SDL_RenderCopy(screenRenderer, _spriteImage, NULL, &rect);
}

void Sprite::SetSprite(SDL_Texture* sprite)
{
    _spriteImage = sprite;
    sprite = nullptr;

    /*if (_spriteImage)
        delete _spriteImage;
    else 
    {
        
    }
    sprite = nullptr;*/
}
