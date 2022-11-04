#include "game.h"

game* myGame = nullptr;

int main(int argc, char* argv[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	myGame = new game();

	myGame->init("My Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (myGame->running()) { //game is runing

		frameStart = SDL_GetTicks();

		//handle any user input
		myGame->handleEvents();
		//update all objects in eg. posisitions etc.
		myGame->update();
		//render changes to the display
		myGame->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	myGame->clean();

	return 0;
}