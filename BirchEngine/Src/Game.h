#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include <SDL_mixer.h>
//#include "ECS/Button.h"

class AssetManager;
class ColliderComponent;

class Game
{
public:
	int currLevel = 0;
	std::vector<bool> myLevels = {false, false, false};
	int enemyLeft = 0;
	bool finish = false;

	Game();
	~Game();

	int width, height;

	void init(const char* title, int width, int height, bool fullscreen);
	void updateMap(int level);
	void handleEvents();
	void update();
	bool running() { return isRunning; }
	int attackedTimer = 0;
	void render();
	void clean();
	void addEnemies(int x, int y, int tHealth);
	void setting();
	static void changeMap(Map* tmap);

	static SDL_Renderer *renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager* assets;
	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles,
		groupEnemies,
		groupSMap,
		GroupUI
	};

	SDL_Window* getWindow() {
		return window;
	};

	Vector2D playerPos;
	Vector2D enemyPos;
	SDL_Window* window;
	SDL_Window* settWindow;
	bool mapLoaded = false;
	bool map1 = false;
	

private:

	int cnt = 0;
	
};