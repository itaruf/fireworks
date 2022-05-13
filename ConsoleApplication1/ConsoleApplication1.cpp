#include "ConsoleApplication1.h"

//Screen dimension constants
int main(int argc, char* argv[])
{
	int imgFlags{ IMG_INIT_PNG };

	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	TTF_Init();

	//The surface contained by the window

	SDLWindow window("Oh la belle bleue", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720);

	if (!window.window)
	{
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		TTF_Quit();
		SDL_Quit();
		return 1;
	}
	
	SDL_Renderer* screenRenderer{ SDL_CreateRenderer(window.window, -1, SDL_RENDERER_ACCELERATED) };

	if (!screenRenderer)
	{
		std::cout << "SDL surface could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_DestroyRenderer(screenRenderer);
		return 1;
	}

	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		SDL_DestroyRenderer(screenRenderer);
		return 1;
	}

	Game* game{ new Game(true, 5, "blanc", 1, screenRenderer) };

	if (!game->IsRunning())
	{
		std::cout << "Game could not be Initialized!" << std::endl;
		TTF_Quit();
		SDL_Quit();
		SDL_DestroyRenderer(screenRenderer);
		return 1;
	}

	//dirty font for fps
	Font* font{ new Font("arial.ttf", 16) };
	
	SDL_Color color{ 255, 0, 0, 255 };

	SDL_Texture* fontTexture{ font->CreateTextTexture("0 FPS", color, screenRenderer) };

	while (game->IsRunning())
	{
		int texW{ 0 };
		int texH{ 0 };

		char fpsmessage[255];

		https://thenumbat.github.io/cpp-course/sdl2/08/08.html

		Uint32 startTicks{ SDL_GetTicks() };

		//let the cpu sleep a litle
		SDL_Delay(30);

		Uint32 endTicks{ SDL_GetTicks() };
		float elapsed{ 1.0f / ((endTicks - startTicks) / 1000.0f) };

		snprintf(fpsmessage, 255, "%f FPS", elapsed);
		fontTexture = font->CreateTextTexture(fpsmessage, color, screenRenderer);
		SDL_QueryTexture(fontTexture, NULL, NULL, &texW, &texH);
		SDL_Rect fontDstRec{ 0, 0, texW, texH };

		game->Update(elapsed);
		game->Render(screenRenderer);
		SDL_RenderCopy(screenRenderer, fontTexture, NULL, &fontDstRec);
		SDL_RenderPresent(screenRenderer);
		SDL_UpdateWindowSurface(window.window);
	}

	SDL_Delay(1000);

	SDL_DestroyTexture(fontTexture);
	SDL_DestroyRenderer(screenRenderer);

	delete game;
	delete font;


	return 0;
}
