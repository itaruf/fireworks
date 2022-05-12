#include <iostream>
#include <SDL.h>
#include <SDL_Image.h>

#include "Game.h"
#include <SDL_ttf.h>
#include "Font.h"

//Screen dimension constants
int main(int argc, char* argv[])
{
	int imgFlags = IMG_INIT_PNG;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	TTF_Init();

	//The surface contained by the window
	SDL_Renderer* screenRenderer = nullptr;

	SDL_Window* window = SDL_CreateWindow
	("Oh la belle bleue", // window's title
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, // coordinates on the screen, in pixels, of the window's upper left corner
		1280, 720, // window's length and height in pixels  
		SDL_WINDOW_OPENGL);
	if (window == nullptr)
	{
		std::cout <<  "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		goto exit;
	}

	screenRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (screenRenderer == nullptr)
	{
		std::cout << "SDL surface could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		goto exit2;
	}

	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		goto exit2;
	}

	//brackets here are due to game being declared after goto. we could also move the variable declaration bit from an init order point of view it's better this way
	{
		Game* game = new Game();
		if (!game->Init(screenRenderer))
		{
			std::cout << "Game could not be Initialized!" << std::endl; 
			goto exit;
		}

		//main loop

		int lastTickTime = SDL_GetTicks();
		int lastFpsTime = lastTickTime;
		//dirty font for fps
		Font* font = new Font("arial.ttf", 16);
		auto fontTexture = font->CreateTextTexture("0 FPS", SDL_Color{ 255, 0, 0,255 }, screenRenderer);
		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(fontTexture, NULL, NULL, &texW, &texH);
		SDL_Rect fontDstRec = { 0, 0, texW, texH };
		int fpsCount = 0;
		char fpsmessage[255];

		while (game->IsRunning()) {
			int now = SDL_GetTicks();
			int deltaTime = now - lastTickTime;


			if (lastFpsTime + 1000 <= now) {
				lastFpsTime = now;
				snprintf(fpsmessage, 255, "%d FPS", fpsCount);
				fontTexture = font->CreateTextTexture(fpsmessage, SDL_Color{ 255, 0, 0,255 }, screenRenderer);
				SDL_QueryTexture(fontTexture, NULL, NULL, &texW, &texH);
				fontDstRec = { 0, 0, texW, texH };
				fpsCount = 0;
			}
			++fpsCount;


			game->Update(deltaTime);

			lastTickTime = now;

			game->Render(screenRenderer);
				
			SDL_RenderCopy(screenRenderer, fontTexture, NULL, &fontDstRec);
				
			SDL_RenderPresent(screenRenderer);
			SDL_UpdateWindowSurface(window);

			//let the cpu sleep a litlle
			SDL_Delay(30);

		}

		SDL_DestroyTexture(fontTexture);
		delete game;
		delete font;
	}

	SDL_DestroyRenderer(screenRenderer);

exit2:
	SDL_DestroyWindow(window);

exit:
	TTF_Quit();
	SDL_Quit();

	return 0;
}
