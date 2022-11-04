#include "Map.h"
#include "TextureManager.h"

int level_one[20][25] = {

	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,2,2,2,0,0,2,2,1,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

Map::Map() {
	dirt = TextureManager::LoadTexture("Assets/dirt.png");
	grass = TextureManager::LoadTexture("Assets/grass.png");
	water = TextureManager::LoadTexture("Assets/water.png");

	loadMap(level_one);

	src.x = src.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;

	dest.x = dest.y = 0;

}

void Map::loadMap(int arr[20][25]) {

	for (int row = 0; row < 20; row++) {
		for (int column = 0; column < 25; column++) {
			map[row][column] = arr[row][column];
		}
	}

}

void Map::drawMap() {


	int type = 0;
	for (int row = 0; row < 20; row++) {
		for (int column = 0; column < 25; column++) {

			type = map[row][column];
			dest.x = column * 32;
			dest.y = row * 32;

			switch (type) {
			case 0:
				TextureManager::draw(water, src, dest);
				break;
			case 1:
				TextureManager::draw(grass, src, dest);
				break;
			case 2:
				TextureManager::draw(dirt, src, dest);
				break;
			default:
				break;
			}
		}
	}

}
/*Added Texture Map functionality( This is under Map.cpp and Map.h). This allows for drawing the map the player is currently on. Also added The Entity Component System(This is under ECS.h and Components.h). This allows us to better manage the Entities in our system, i.e players/ai.V2*/