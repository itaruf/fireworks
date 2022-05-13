#include "Game.h"


Game::~Game()
{
    std::cout << "GAME DESTRUCTOR CALLED " << std::endl;
    for (const auto& generateur : _generateurs)
    {
        delete generateur;
    }
}

Game::Game(bool isRunning, int nbGenerateur, std::string couleur, int modele, SDL_Renderer * screenRenderer) : _modele{ modele }, _nbGenerateur{ nbGenerateur }, _couleur{ std::move(couleur) }, _isRunning{ true }, _screenRenderer{ screenRenderer }
{
    /*_generateurs.resize(nbGenerateur);
    std::cout << _generateurs.capacity() << std::endl;*/
    srand(time(NULL));
}

void Game::Update(int deltaTime)
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
        case SDL_QUIT:
            _isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                _isRunning = false;
                break;
            case SDLK_1:
                _couleur = "blanc";
                break;
            case SDLK_2:
                _couleur = "rouge";
                break;
            case SDLK_3:
                _couleur = "vert";
                break;
            case SDLK_4:
                _couleur = "bleu";
                break;
            case SDLK_9:
                _modele = 1;
                break;
            case SDLK_0:
                _modele = 2;
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (e.button.button) 
            {
            case 1:
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                CreerGenerateurParticule(mouseX, mouseY);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    if (_isRunning)
    {
        for (auto& generateur : _generateurs) 
        {
            if (!generateur)
                continue;

            if (!generateur->EstActif())
            {
                auto tmp = generateur;
                _generateurs.erase(std::find(_generateurs.begin(), _generateurs.end(), tmp));
                delete tmp;
            }
            else
            {
                generateur->Update(deltaTime);
            }
        }
    }
}

void Game::Render(SDL_Renderer* screenRenderer)
{
    SDL_RenderClear(screenRenderer);

	if (_isRunning)
    {
        for (const auto& generateur : _generateurs)
        {
            if (!generateur)
                continue;
            generateur->Render(screenRenderer);
        }
    }
}

bool Game::IsRunning()
{
	return _isRunning;
}

void Game::CreerGenerateurParticule(int posX, int posY)
{
    if (_generateurs.size() == _nbGenerateur)
    {
        auto generator{ _generateurs[0] };
        _generateurs.erase(_generateurs.begin());
        delete generator;
    }
    Vector* position{ new Vector(posX, posY) };
    auto generateur{ new GenerateurParticule(_screenRenderer, rand() % 20, 20 + rand() % 80, 500 + rand() % 2500, "particle" + std::to_string(_modele), _couleur, rand() % 5, rand() % 15, position, 16, 64, 100 + rand() % 500, rand() % 90) };
    _generateurs.emplace_back(generateur);
    position = nullptr;
}
