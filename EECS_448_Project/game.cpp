#include "game.h"
#include "TextureManager.h"
#include "GameObject.h"
using namespace std;

GameObject* player;
//GameObject* enemy;

game::game() {
	
}

game::~game(){

}

void game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING)== 0) {
		cout << "Subsystems Initialized!.." << endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window) {
			cout << "Window Created" << endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
			cout << "Renderer created!" << endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	player = new GameObject("Assets/player.png", renderer, 0, 0);
	//enemy = new GameObject("Assets/player.png", renderer, 50, 50);

}

void game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch(event.type){
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void game::update() {
	cnt++;

	player->Update();

	cout << cnt << endl;
}

void game::render() {
	SDL_RenderClear(renderer);
	//this is where we would add stuff to render
	player->Render();
	//enemy->Render();
	SDL_RenderPresent(renderer);

}

void game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game Cleaned";
}

