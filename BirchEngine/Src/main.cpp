#include "Game.h"
#include <SDL_ttf.h>
#include <SDL.h>

Game *game = nullptr;

int main(int argc, char *argv[])
{

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	SDL_Texture* labelTexture;
	TTF_Font* myFont;
	std::string tempString = "0";

	game = new Game();
	game->init("GameWindow", 1280, 720, false);

	while (game->running())
	{

		frameStart = SDL_GetTicks();

		if (game->settingWindow)
			game->setting();
		game->handleEvents();
		game->update(tempString);
		game->render();
		

		frameTime = SDL_GetTicks() - frameStart;
		
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
		
		 tempString = "FPS: " + std::to_string((int)(1000 / frameTime));
		 

	}

	game->clean();
	return 0;
}