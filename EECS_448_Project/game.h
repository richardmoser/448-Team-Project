#ifndef GAME_H
#define GAME_H
#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <iostream>

class game {

public:
	game();
	~game();

	//create our game window
	//@param tite - The title of the window, xpos - The x Position of the window, ypos - The y Posistion of the window, width - The width of the window, height - the Height of the window, fullscreen - wether or not we want to render fullscreen or not(false - windowed, true- fullscreen)
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	//handle all of the events in the game
	void handleEvents();
	//update characters, items, etc
	void update();
	//create renderer
	void render();
	//destroys our game window
	void clean();

	bool running() { return isRunning; };

	static SDL_Renderer* renderer;

private:
	bool isRunning;
	SDL_Window *window;
	int cnt = 0;

};

#endif // !GAME_H

