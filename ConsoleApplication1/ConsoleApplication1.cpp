#include "ConsoleApplication1.h"

void DeInitialize();
//Screen dimension constants
int main(int argc, char* argv[])
{
	int imgFlags{ IMG_INIT_PNG };

	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
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
		SDLRenderer renderer{ window.CreateRenderer(-1, SDL_RENDERER_ACCELERATED) };

		if (!renderer.renderer)
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
			Game game{ true, 5, "blanc", 1, renderer.renderer };

			if (!game.IsRunning())
			{
				std::cout << "Game could not be Initialized!" << std::endl;
				goto exit;
			}

			else {

				SDL_Color color{ 255, 0, 0, 255 };

				while (game.IsRunning())
				{
					int texW{ 0 };
					int texH{ 0 };

					char fpsmessage[255];

					//https://thenumbat.github.io/cpp-course/sdl2/08/08.html

					Uint32 startTicks{ SDL_GetTicks() };

					//let the cpu sleep a litle
					SDL_Delay(15); // 60 fps

					Uint32 endTicks{ SDL_GetTicks() };
					int elapsed{ (int)(1.0f / ((endTicks - startTicks) / 1000.0f)) };

					/*std::cout << renderer.renderer << std::endl;*/
					/*std::cout << &renderer << std::endl;*/

					snprintf(fpsmessage, 255, "%d FPS", elapsed);
					SDLTexture texture{ SDLTexture::FromSurface(renderer, fpsmessage, color) };
					SDL_QueryTexture(texture._texture, NULL, NULL, &texW, &texH);
					SDL_Rect fontDstRec{ 0, 0, texW, texH };

					game.Update(elapsed);
					game.Render(renderer);
					SDL_RenderCopy(renderer.renderer, texture._texture, NULL, &fontDstRec);
					SDL_RenderPresent(renderer.renderer);
					SDL_UpdateWindowSurface(window.window);
				}
				goto exit;
			}
		}
	}

exit:
	DeInitialize();
	return 0;
}

inline void DeInitialize()
{
	TTF_Quit();
	SDL_Quit();
}
