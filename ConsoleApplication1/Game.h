#pragma once

#ifndef GAME_H
#define GAME_H

#include <SDL_render.h>
#include "GenerateurParticule.h"
#include <string>
#include <vector>
#include <SDL.h>
#include <iostream>
#include <SDL_scancode.h>
#include "Font.h"
#include <time.h>

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

	void Update(int deltaTime);

	void Render(SDL_Renderer* screenRenderer);

	bool IsRunning();

	void CreerGenerateurParticule(int posX, int posY);
};

#endif GAME_H