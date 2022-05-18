#include "Game.h"

Game::~Game()
{
    std::cout << "GAME DESTRUCTOR CALLED " << std::endl;
    for (auto& generateur : _generateurs)
        delete generateur;
    _generateurs.clear();
}

Game::Game(bool isRunning, int nbGenerateur, std::string couleur, int modele, SDL_Renderer* screenRenderer) : _modele{ modele }, _nbGenerateur{ nbGenerateur }, _couleur{ std::move(couleur) }, _isRunning{ isRunning }, _screenRenderer{ screenRenderer }
{
    std::cout << "GAME CONSTRUCTOR CALLED" << std::endl;

    for (int i = 0; i < _nbGenerateur; ++i)
        _generateurs.emplace_back(nullptr);
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
            if (e.button.button == 1)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                CreerGenerateurParticule(mouseX, mouseY);
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
                continue;

            generateur->Update(deltaTime);
        }
    }
}

void Game::Render(SDLRenderer& screenRenderer)
{
    SDL_RenderClear(screenRenderer.renderer);

    if (_isRunning)
    {
        for (auto& generateur : _generateurs)
        {
            if (!generateur)
                continue;

            if (!generateur->EstActif())
                continue;

            generateur->Render(screenRenderer);
        }
    }
}

void Game::CreerGenerateurParticule(int posX, int posY)
{
    //https://www.gormanalysis.com/blog/random-numbers-in-cpp/
    std::random_device myRandomDevice;
    unsigned seed = myRandomDevice();
    std::default_random_engine myRandomEngine(seed);

    Vector pos{ posX, posY };

    for (auto& generateur : _generateurs)
    {
        if (!generateur || !generateur->EstActif())
        {
            delete generateur;
            generateur = new GenerateurParticule(_screenRenderer, myRandomDevice() % 20, 20 + myRandomDevice() % 80, 500 + myRandomDevice() % 2500, "particle" + std::to_string(_modele), _couleur, myRandomDevice() % 5, myRandomDevice() % 15, pos, 16, 64, 100 + myRandomDevice() % 500, myRandomDevice() % 90);
            return;
        }
    }

    std::cout << "Replacing First" << std::endl;
    delete _generateurs[0];
    _generateurs[0] = new GenerateurParticule(_screenRenderer, myRandomDevice() % 20, 20 + myRandomDevice() % 80, 500 + myRandomDevice() % 2500, "particle" + std::to_string(_modele), _couleur, myRandomDevice() % 5, myRandomDevice() % 15, pos, 16, 64, 100 + myRandomDevice() % 500, myRandomDevice() % 90);
}
