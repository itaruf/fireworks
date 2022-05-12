#pragma once
#include <SDL_render.h>
#include "GenerateurParticule.h"
#include <string>
#include <vector>

class IGameEntity;

class Game
{
private:

    bool _isRunning;
	int _nbGenerateur;
	std::vector<GenerateurParticule*> _generateurs;
	int _modele;
	std::string _couleur;
	SDL_Renderer* _screenRenderer;

public:
	Game(bool isRunning, int nbGenerateur, std::string couleur, int modele, SDL_Renderer* screenRenderer);
	~Game();
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;

	bool Init(SDL_Renderer* screenRenderer);
	void Release();

	void Update(int deltaTime);

	void Render(SDL_Renderer* screenRenderer);

	bool IsRunning();

	void CreerGenerateurParticule(int posX, int posY);
};

