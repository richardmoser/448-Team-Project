#include "Game.h"
#include "TextureManager.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& enemy(manager.addEntity());
auto& player(manager.addEntity());
auto& label(manager.addEntity());
auto& label2(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}



void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	assets->AddTexture("terrain", "assets/terrain_ss.png");
	assets->AddTexture("player", "assets/player_anims.png");
	assets->AddTexture("enemy", "assets/enemy_anims.png");
	assets->AddTexture("projectile", "assets/proj.png");

	assets->AddFont("arial", "assets/arial.ttf", 16);

	map = new Map("terrain", 3, 32);
	//ecs implementation
	SDL_Color white = { 255, 255, 255, 255 };
	map->LoadMap("assets/map.map", 25, 20);

	player.addComponent<TransformComponent>(800.0f, 640.0f, 32 , 32, 4);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	//player.addComponent<HitboxComponent>(&enemyPos, &playerPos);
	player.addComponent<ColliderComponent>("player", player.getComponent<TransformComponent>().position.x, player.getComponent<TransformComponent>().position.y, 50);//, player.getComponent<SpriteComponent>().srcRect.h, player.getComponent<SpriteComponent>().srcRect.w);
	player.addGroup(groupPlayers);
	player.addComponent<UILabel>(10, 400 , "Test String", "arial", white);

	enemy.addComponent<TransformComponent>(800.0f, 800.0f, 32, 32, 4);
	enemy.addComponent<SpriteComponent>("enemy", true);
	//enemy.addComponent<HitboxComponent>(&playerPos, &enemyPos);
	enemy.addComponent<ColliderComponent>("enemy", enemy.getComponent<TransformComponent>().position.x, enemy.getComponent<TransformComponent>().position.y, 50);//, enemy.getComponent<SpriteComponent>().srcRect.h, enemy.getComponent<SpriteComponent>().srcRect.w);
	enemy.addGroup(groupEnemies);
	enemy.addComponent<UILabel>(500, 400, "Test String", "arial", white);

	
	
	label.addComponent<UILabel>(10, 10, "Test String", "arial", white);
	label2.addComponent<UILabel>(500, 10, "Test String", "arial", white);

	assets->CreateProjectile(Vector2D(600, 600), Vector2D(2,0),200, 2, "projectile");
	assets->CreateProjectile(Vector2D(600, 620), Vector2D(2, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(400, 600), Vector2D(2, 1), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, -1), 200, 2, "projectile");

}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::changeMap(Map* tmap) {
	
    
	map = tmap;
	auto& tiles(manager.getGroup(Game::groupMap));

	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}


}

void Game::handleEvents()
{
	
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}



void Game::update()
{	

	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	playerPos = player.getComponent<TransformComponent>().position;
	enemyPos = enemy.getComponent<TransformComponent>().position;


	int playerHealth = player.getComponent<SpriteComponent>().health;
	int enemyHealth = enemy.getComponent<SpriteComponent>().health;
	
	std::stringstream ss, ss1, ss2, ss3;
	ss << "Player position: " << playerPos << ", velocity: " << player.getComponent<TransformComponent>().velocity;
	ss1 << "Enemy position: " << enemyPos << ", velocity: " <<  enemy.getComponent<TransformComponent>().velocity;
	ss2 << "Health: " << playerHealth;
	ss3 << "Enemy Health: " << enemyHealth;
	enemy.getComponent<UILabel>().changePos(enemy.getComponent<TransformComponent>().position.x - 600, enemy.getComponent<TransformComponent>().position.y - 600);
	player.getComponent<UILabel>().changePos(player.getComponent<TransformComponent>().position.x - 600, player.getComponent<TransformComponent>().position.y - 600);
	label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");
	label2.getComponent<UILabel>().SetLabelText(ss1.str(), "arial");
	player.getComponent<UILabel>().SetLabelText(ss2.str(), "arial");
	enemy.getComponent<UILabel>().SetLabelText(ss3.str(), "arial");
	
	
	manager.refresh();
	manager.update();

	
	for (auto& c : enemies)
	{
		
		if(!(Collision::AABB(player.getComponent<ColliderComponent>().collider, c->getComponent<ColliderComponent>().collider))) {
			
			if (playerPos.x + 30 > c->getComponent<TransformComponent>().position.x)
				c->getComponent<TransformComponent>().velocity.x = 0.5;
			if(playerPos.x + 30 < c->getComponent<TransformComponent>().position.x)
				c->getComponent<TransformComponent>().velocity.x = -0.5;
			if (playerPos.y - 30 < c->getComponent<TransformComponent>().position.y)
				c->getComponent<TransformComponent>().velocity.y = -0.5;
			if (playerPos.y - 30 >  c->getComponent<TransformComponent>().position.y)
				c->getComponent<TransformComponent>().velocity.y = 0.5;
			

		
		}
		else {
			c->getComponent<TransformComponent>().velocity.y = 0;
			c->getComponent<TransformComponent>().velocity.x = 0;
		}

		
			

		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, c->getComponent<ColliderComponent>().collider))
		{
			if (event.type == SDL_KEYDOWN && SDLK_f) {
				c->getComponent<SpriteComponent>().attack();
			}
			//player.getComponent<TransformComponent>().position = playerPos;
			player.getComponent<TransformComponent>().position = playerPos;
			std::cout << "Player ran into another";

		}
	}

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, c->getComponent<ColliderComponent>().collider))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "Hit player!" << std::endl;
			p->destroy();
		}
	}

	camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 400);
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 320);

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& c : colliders)
	{
		c->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& e : enemies)
	{
		e->draw();
	}

	for (auto& p : projectiles)
	{
		p->draw();
	}

	label.draw();
	label2.draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}