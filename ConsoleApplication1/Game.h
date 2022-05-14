#pragma once

#ifndef GAME_H
#define GAME_H

#include <SDL_render.h>
#include <SDL.h>
#include <SDL_scancode.h>

#include "GenerateurParticule.h"
#include "Font.h"

#include <time.h>
#include <random>
#include "SDLRenderer.h"

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

	void Update(int deltaTime);
	void Render(SDLRenderer& screenRenderer);
	bool IsRunning();
	void CreerGenerateurParticule(int posX, int posY);
};

inline bool Game::IsRunning()
{
	return _isRunning;
}

#endif GAME_H