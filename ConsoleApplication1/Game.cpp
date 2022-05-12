#include "Game.h"
#include <SDL.h>
#include <iostream>
#include <SDL_scancode.h>
#include "Font.h"
#include <time.h>
#include "GenerateurParticule.h"

Game::~Game() = default;

bool Game::Init(SDL_Renderer * screenRenderer)
{
    _modele = 1;
    _couleur = "blanc";
    _isRunning = true;
    _screenRenderer = screenRenderer;
    srand(time(NULL));
	return true;
}

void Game::Update(int deltaTime)
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            _isRunning = false;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            if(e.key.keysym.sym == SDLK_ESCAPE)
            {
                _isRunning = false;
            }
            if (e.key.keysym.sym == SDLK_1)
            {
                _couleur = "blanc";
            }
            if (e.key.keysym.sym == SDLK_2)
            {
                _couleur = "rouge";
            }
            if (e.key.keysym.sym == SDLK_3)
            {
                _couleur = "vert";
            }
            if (e.key.keysym.sym == SDLK_4)
            {
                _couleur = "bleu";
            }
            if (e.key.keysym.sym == SDLK_9)
            {
                _modele = 1;
            }
            if (e.key.keysym.sym == SDLK_0)
            {
                _modele = 2;
            }
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (e.button.button == 1)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                CreerGenerateurParticule(mouseX, mouseY);
            }
        }
    }

    if (_isRunning)
    {
        for(int i = 0; i < _generateurs.size(); i++)
        {
            if (!_generateurs[i]->EstActif())
            {
                auto generateur = _generateurs[i];
                _generateurs.erase(std::find(_generateurs.begin(), _generateurs.end(), generateur));
                delete generateur;
            }
            else
            {
                _generateurs[i]->Update(deltaTime);
            }
        }
    }
}

void Game::Render(SDL_Renderer* screenRenderer)
{
    SDL_RenderClear(screenRenderer);
    /*std::cout << _isRunning << std::endl;*/

	if (_isRunning)
    {
        for (int i = 0; i < _generateurs.size(); i++)
        {
            _generateurs[i]->Render(screenRenderer);
        }
    }
}

void Game::Release()
{
    for (int i = 0; i < _generateurs.size(); i++)
    {
        delete _generateurs[i];
    }
    _generateurs.clear();
}


bool Game::IsRunning()
{
	return _isRunning;
}

void Game::CreerGenerateurParticule(int posX, int posY)
{
    if (_generateurs.size() == 5)
    {
        auto generator = _generateurs[0];
        _generateurs.erase(_generateurs.begin());
        delete generator;
    }
    Vector* position = new Vector(posX, posY);
    auto generateur = new GenerateurParticule();
    generateur->Init(_screenRenderer, rand() % 20, 20 + rand() % 80, 500 + rand() % 2500, "particle" + std::to_string(_modele), _couleur, rand() % 5, rand() % 15, position, 16, 64, 100 + rand() % 500, rand() % 90);
    _generateurs.push_back(generateur);
}
