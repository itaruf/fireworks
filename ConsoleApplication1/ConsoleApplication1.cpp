#include "ConsoleApplication1.h"

//Screen dimension constants
int main(int argc, char* argv[])
{
	int imgFlags{ IMG_INIT_PNG };

	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 0;
	}
	TTF_Init();

	//The surface contained by the window
	SDLWindow window("Oh la belle bleue", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720);

	if (!window.window)
	{
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		goto exit;
	}

	{
		/*SDLRenderer renderer{ window.CreateRenderer(-1, SDL_RENDERER_ACCELERATED) };*/
		std::shared_ptr<SDL_Renderer> renderer(SDL_CreateRenderer(window.window, -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);

		if (!renderer)
		{
			std::cout << "SDL surface could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			goto exit;
		}

		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			goto exit;
		}

		{
			Game* game{ new Game(true, 5, "blanc", 1, renderer) };

			if (!game->IsRunning())
				std::cout << "Game could not be Initialized!" << std::endl;				

			else 
			{
				SDL_Color color{ 255, 0, 0, 255 };

				while (game->IsRunning())
				{
					int texW{ 0 };
					int texH{ 0 };

					//https://thenumbat.github.io/cpp-course/sdl2/08/08.html

					Uint32 startTicks{ SDL_GetTicks() };

					//let the cpu sleep a litle
					SDL_Delay(15); // 60 fps

					Uint32 endTicks{ SDL_GetTicks() };

					int elapsed{ (int)(1.0f / ((endTicks - startTicks) / 1000.0f)) };

					std::string message = std::to_string(elapsed) + " FPS";
					SDLTexture texture{ SDLTexture::FromSurface(renderer, std::move(message), color) };
					SDL_QueryTexture(texture._texture, NULL, NULL, &texW, &texH);
					SDL_Rect fontDstRec{ 0, 0, texW, texH };

					game->Update(elapsed);
					game->Render();
					SDL_RenderCopy(renderer.get(), texture._texture, NULL, &fontDstRec);
					SDL_RenderPresent(renderer.get());
					SDL_UpdateWindowSurface(window.window);
				}
			}
			delete game;
			goto exit;
		}
	}

exit:
	TTF_Quit();
	SDL_Quit();

	// Laisser le temps de prendre un snapshot
	Sleep(1000);

	return 0;
}