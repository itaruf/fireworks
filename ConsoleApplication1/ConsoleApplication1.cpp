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

	SDLRenderer renderer{ window.CreateRenderer(-1, SDL_RENDERER_ACCELERATED) };

	if (!renderer.renderer)
	{
		std::cout << "SDL surface could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return 1;
	}

	Game* game{ new Game(true, 5, "blanc", 1, renderer.renderer) };

	if (!game->IsRunning())
	{
		std::cout << "Game could not be Initialized!" << std::endl;
		TTF_Quit();
		SDL_Quit();
		return 1;
	}

	//dirty font for fps

	SDL_Color color{ 255, 0, 0, 255 };
	SDLTexture texture{ SDLTexture::FromSurface(renderer, "0 FPS", color)};

	while (game->IsRunning())
	{
		int texW{ 0 };
		int texH{ 0 };

		char fpsmessage[255];

		//https://thenumbat.github.io/cpp-course/sdl2/08/08.html

		Uint32 startTicks{ SDL_GetTicks() };

		//let the cpu sleep a litle
		SDL_Delay(30);

		Uint32 endTicks{ SDL_GetTicks() };
		int elapsed{(int)(1.0f / ((endTicks - startTicks) / 1000.0f))};

		snprintf(fpsmessage, 255, "%d FPS", elapsed);
		texture = SDLTexture::FromSurface(renderer, fpsmessage, color);
		SDL_QueryTexture(texture._texture, NULL, NULL, &texW, &texH);
		SDL_Rect fontDstRec{ 0, 0, texW, texH };

		game->Update(elapsed);
		game->Render(renderer.renderer);
		SDL_RenderCopy(renderer.renderer, texture._texture, NULL, &fontDstRec);
		SDL_RenderPresent(renderer.renderer);
		SDL_UpdateWindowSurface(window.window);
	}

	delete game;
	/*delete font;*/


	return 0;
}
