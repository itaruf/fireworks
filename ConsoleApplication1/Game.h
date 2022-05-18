#pragma once

#ifndef GAME_H
#define GAME_H

#include <SDL_scancode.h>
#include <SDL.h>
#include <SDL_render.h>

#include "GenerateurParticule.h"
#include "SDLRenderer.h"
#include "Font.h"
#include <random>

struct SDL_Renderer;
class Game
{
private:

    bool _isRunning;
	int _nbGenerateur;
	std::vector<GenerateurParticule*> _generateurs;
	int _modele;
	std::string _couleur;
	std::shared_ptr<SDL_Renderer> _screenRenderer;

public:
	Game(bool isRunning, int nbGenerateur, std::string couleur, int modele, std::shared_ptr<SDL_Renderer> screenRenderer);
	~Game();
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;

	void Update(int deltaTime);
	void Render();
	bool IsRunning();
	void CreerGenerateurParticule(int posX, int posY);
};

inline bool Game::IsRunning()
{
	return _isRunning;
}

#endif GAME_H