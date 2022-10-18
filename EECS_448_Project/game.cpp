#include "game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "ECS.h"
#include "Components.h"
using namespace std;

GameObject* player;
//GameObject* enemy;
Map* map;


SDL_Renderer* game::renderer = nullptr;

Manager manager;
auto& newPlayer(manager.addEntity());

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
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer created!" << endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	player = new GameObject("Assets/player.png", 0, 0);
	//enemy = new GameObject("Assets/player.png", 50, 50);
	map = new Map();
	newPlayer.addComponent<PosistionComponent>();
	newPlayer.addComponent<PosistionComponent>().setPos(500, 500);
	

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
	manager.update();
	std::cout << '\n' << newPlayer.getComponent<PosistionComponent>().x() << " " << newPlayer.getComponent<PosistionComponent>().y() << std::endl;

	cout << cnt << endl;
}

void game::render() {
	SDL_RenderClear(renderer);
	map->drawMap();
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

