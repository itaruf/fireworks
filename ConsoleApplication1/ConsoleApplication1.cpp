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

	SDL_Window* window{ SDL_CreateWindow
	("Oh la belle bleue", // window's title
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, // coordinates on the screen, in pixels, of the window's upper left corner
		1280, 720, // window's length and height in pixels  
		SDL_WINDOW_OPENGL
	)};

	/*if (!window)
	{
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		TTF_Quit();
		SDL_Quit();
		SDL_DestroyWindow(window);
		return 1;
	}*/
	
	SDL_Renderer* screenRenderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED) };

	/*if (!screenRenderer)
	{
		std::cout << "SDL surface could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(screenRenderer);
		return 1;
	}*/

	/*if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(screenRenderer);
		return 1;
	}*/

	Game* game{ new Game(true, 5, "blanc", 1, screenRenderer) };

	if (!game->IsRunning())
	{
		std::cout << "Game could not be Initialized!" << std::endl;
		TTF_Quit();
		SDL_Quit();
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(screenRenderer);
		return 1;
	}

	//main loop

	auto lastTickTime{ SDL_GetTicks() };
	auto lastFpsTime{ lastTickTime };

	//dirty font for fps
	std::string str{ "arial.ttf" };
	Font* font{ new Font(std::move(str), 16) };

	SDL_Color color{ 255, 0, 0, 255 };
	
	str = "0 FPS";

	auto fontTexture{ font->CreateTextTexture(std::move(str), color, screenRenderer) };
	auto texW{ 0 };
	auto texH{ 0 };
	SDL_QueryTexture(fontTexture, NULL, NULL, &texW, &texH);
	SDL_Rect fontDstRec{ 0, 0, texW, texH };
	auto fpsCount{ 0 };
	char fpsmessage[255];

	while (game->IsRunning())
	{
		/*std::cout << sharedScreen.use_count() << std::endl;*/

		auto now{ SDL_GetTicks() };
		auto deltaTime{ now - lastTickTime };
		auto time{ lastFpsTime + 1000 };

		if (time <= now)
		{
			lastFpsTime = now;
			snprintf(fpsmessage, 255, "%d FPS", fpsCount);
			
			fontTexture = font->CreateTextTexture(fpsmessage, color, screenRenderer);
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
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(screenRenderer);
	delete game;
	delete font;

	return 0;
}
