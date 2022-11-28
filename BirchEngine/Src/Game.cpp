//#include "Game.h"
#include "TextureManager.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <fstream>
#include <sstream>
#include "ECS/Button.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Color white = { 255, 255, 255, 255 };

SDL_Rect Game::camera = { 0,0,3750,0};

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

int init2 = Mix_Init(MIX_INIT_MP3);
Mix_Chunk* sound;


auto& player(manager.addEntity());
//auto& door(manager.addEntity());
auto& label(manager.addEntity());
auto& label2(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}



void Game::init(const char* title, int width, int height, bool fullscreen)
{
	this->width = width;
	this->height = height;
	
	int flags = 0;


	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	//Mix_Music* music = Mix_LoadMUS("assets/the_rainbow_train.mp3");
	 //sound = Mix_LoadWAV("assets/sword.mp3"); //For playing audio effects;

	//Mix_PlayMusic(music, 10);
	
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");


	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, 00, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
		}

		isRunning = true;
	}

	if (TTF_Init() == 00)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	//assets->AddTexture("Level1", "assets/level1.png");
	assets->AddTexture("player", "assets/player_anims.png");
	assets->AddTexture("enemy", "assets/enemy_anims.png");
	assets->AddTexture("projectile", "assets/proj.png");
	//assets->AddTexture("door", "assets/.png");

	assets->AddFont("arial", "assets/arial.ttf", 16);

	//map = new Map("Level1", 3, 32, 32);
	//ecs implementation

	//map->LoadMap("assets/map.map", 25, 20,0);

	
	
		player.addComponent<TransformComponent>(60.0f, 300.0f, 32, 32, 4);
		player.addComponent<SpriteComponent>("player", true);
		player.addComponent<KeyboardController>();
		player.getComponent<TransformComponent>().velocity.y = 0.75f;
		//player.addComponent<HitboxComponent>(&enemyPos, &playerPos);
		player.addComponent<ColliderComponent>("player", player.getComponent<TransformComponent>().position.x, player.getComponent<TransformComponent>().position.y, 1);//, player.getComponent<SpriteComponent>().srcRect.h, player.getComponent<SpriteComponent>().srcRect.w);
		player.addGroup(groupPlayers);
		player.addComponent<UILabel>(10, 400, "Test String", "arial", white);

		//door.addComponent<TransformComponent>(4670.00f, 560.0f, 32, 32, 4);
		//player.addComponent<SpriteComponent>("player", true);

	//addEnemies(1);

	/*
	enemy.addComponent<TransformComponent>(800.0f, 800.0f, 32, 32, 4);
	enemy.addComponent<SpriteComponent>("enemy", true);
	//enemy.addComponent<HitboxComponent>(&playerPos, &enemyPos);
	enemy.addComponent<ColliderComponent>("enemy", enemy.getComponent<TransformComponent>().position.x, enemy.getComponent<TransformComponent>().position.y, 50);//, enemy.getComponent<SpriteComponent>().srcRect.h, enemy.getComponent<SpriteComponent>().srcRect.w);
	enemy.addGroup(groupEnemies);
	enemy.addComponent<UILabel>(500, 400, "Test String", "arial", white);
	*/
	
	
	label.addComponent<UILabel>(0, 0, "Test String", "arial", white);
	label2.addComponent<UILabel>(500, 10, "Test String", "arial", white);

	//assets->CreateProjectile(Vector2D(600, 600), Vector2D(2,0),200, 2, "projectile");
	//assets->CreateProjectile(Vector2D(600, 620), Vector2D(2, 0), 200, 2, "projectile");
	//assets->CreateProjectile(Vector2D(400, 600), Vector2D(2, 1), 200, 2, "projectile");
	//assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, 00), 200, 2, "projectile");

}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& UI(manager.getGroup(Game::GroupUI));

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

void Game::addEnemies(int x, int y, int tHealth) {

	//for (int i = 0; i < ammt; i++) {
		auto& enemy(manager.addEntity());
		enemy.addComponent<TransformComponent>(x, y, 32, 32, 4);
		enemy.getComponent<TransformComponent>().velocity.y = 0.75f;
		enemy.addComponent<SpriteComponent>("enemy", true);
		//enemy.addComponent<HitboxComponent>(&playerPos, &enemyPos);
		enemy.addComponent<ColliderComponent>("enemy", enemy.getComponent<TransformComponent>().position.x, enemy.getComponent<TransformComponent>().position.y, 1);//, enemy.getComponent<SpriteComponent>().srcRect.h, enemy.getComponent<SpriteComponent>().srcRect.w);
		enemy.addGroup(groupEnemies);
		SDL_Color white = { 255, 255, 255, 255 };
		enemy.addComponent<UILabel>(500, 400, "Test String", "arial", white);
		enemy.getComponent<SpriteComponent>().health = tHealth;
		enemyLeft++;

	//}
}

void Game::setting() {

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);


}

void Game::updateMap(int level) {
	if (level < myLevels.size()) {
		
		enemyLeft = 0;



		Mix_Music* music = Mix_LoadMUS("assets/the_rainbow_train.mp3");
		sound = Mix_LoadWAV("assets/sword.mp3"); //For playing audio effects;

		Mix_PlayMusic(music, 10);


		player.getComponent<TransformComponent>().position = { 60.0f, 488.0f };
		player.getComponent<SpriteComponent>().health = 100;

		while (enemies.size() != 0)
			enemies.pop_back();

		while (tiles.size() != 0)
		tiles.pop_back();

		while (colliders.size() != 0)
			colliders.pop_back();
		
		if (level == 2) {
			SDL_SetRenderDrawColor(renderer, 234, 221, 202, 255);
		}

		//SDL_RenderClear(renderer);
		std::ifstream myFile;
		

		std::string tempString = "assets/level" + std::to_string(level);
		tempString += ".png";
		std::string tempString2 = "assets/level" + std::to_string(level);
		tempString2 += ".map";
		std::string tempString3 = "level" + std::to_string(level);
		std::string tempString4 = "assets/level" + std::to_string(level);
		tempString4+= "1.txt";


		myFile.open(tempString4);

		int scale, pngW, pngH, tw, th, numEN;


		std::cout << "\nThis is file" << tempString2 << "\n";
		//for (int i = 0; i < 5; i++) {
		myFile >> scale;
		myFile >> pngW;
		myFile >> pngH;
		myFile >> tw;
		myFile >> th;
		myFile >> numEN;

		for (int i = 0; i < numEN; i++) {
			int temp1, temp2;
			myFile >> temp1;
			myFile >> temp2;
			addEnemies(temp1, temp2, 100 * level);
		}

		//}

		

		std::cout << "\nThis is scale" << scale << "\n";
		std::cout << "\nThis is pngW" << pngW << "\n";
		std::cout << "\nThis is pngH" << pngH << "\n";
		std::cout << "\nThis is tw" << tw << "\n";
		std::cout << "\nThis is th" << th << "\n";
		//isRunning = false;

		assets->AddTexture(tempString3, tempString.c_str());
		//myFile.close();
		map = new Map(tempString3, scale, pngW);
		//ecs implementation
		map->LoadMap(tempString2, tw, th);
		mapLoaded = true;
		std::cout << "Map " << tempString3 << "loaded\n";
		//manager.update();5

		

		

		
	}
	else {
		isRunning = false;
	}
}


Button* start;
Button* settings;
Button* exitB;
Mouse mouse;

void Game::update()
{

	label.getComponent<UILabel>().changePos(0 - camera.x, 300 - camera.y);
	
	int settingNum = 0;
		if (currLevel == 0) {
			if (!mapLoaded) {
				updateMap(currLevel);
			}
			start = new Button;
			settings = new Button;
			exitB = new Button;
			start->src.y = 0;
			start->dest.x = 1280 / 2 - start->dest.w / 2;
			start->dest.y = 720 / 2 - start->dest.h / 2;

			settings->src.y = 50;
			settings->dest.x = 1280 / 2 - start->dest.w / 2;
			settings->dest.y = 720 / 2 - start->dest.h / 2 + 150;

			exitB->src.y = 100;
			exitB->dest.x = 1280 / 2 - start->dest.w / 2;
			exitB->dest.y = 720 / 2 - start->dest.h / 2 + 300;

			std::cout << "\n" << currLevel;

			start->update(mouse);
			settings->update(mouse);
			exitB->update(mouse);
			mouse.update();

			//mouse.draw();
			std::cout << "\n" << start->dest.x;


			manager.update();
			//manager.refresh();

			if (event.button.button == SDL_BUTTON_LEFT) {
				if (start->isClicked) {
					currLevel++;
					mapLoaded = false;
				}

				if (settings->isClicked && settingNum == 0) {
					
					setting();
				}

				if (exitB->isClicked) {
					isRunning = false;
				}
			}

		}
		else {
			std::cout << "\n" << enemyLeft << "\n";

			if (currLevel > myLevels.size())
				isRunning = false;

			

			if (!mapLoaded) {
				//myLevels[currLevel] = true;
				
				updateMap(currLevel);
				if (currLevel == 1)
					map1 = true;
				
			}

			if (enemyLeft <= 0 && finish) {
				if(map1)
					currLevel++;
				mapLoaded = false;
			}


			for (auto& c : enemies) {
				std::stringstream ss1, ss3;
				enemyPos = c->getComponent<TransformComponent>().position;
				int enemyHealth = c->getComponent<SpriteComponent>().health;
				ss1 << "Enemy position: " << enemyPos << ", velocity: " << c->getComponent<TransformComponent>().velocity;
				ss3 << "Enemy Health: " << enemyHealth;
				c->getComponent<UILabel>().changePos(c->getComponent<TransformComponent>().position.x - c->getComponent<TransformComponent>().velocity.x, c->getComponent<TransformComponent>().position.y - c->getComponent<TransformComponent>().velocity.y);
				c->getComponent<UILabel>().SetLabelText(ss3.str(), "arial");
			}


			SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
			Vector2D playerPos = player.getComponent<TransformComponent>().position;

			manager.update();
			manager.refresh();




			int playerHealth = player.getComponent<SpriteComponent>().health;


			std::stringstream ss1, ss2, ss, ss3;

			ss << "Instructions: Keybinds - A: Move Left, B : Move Right, SPACE : Jump, F : Interact / Attack, ESC : open the menu.Objective : Deafeat the " << enemyLeft << " enemies, then reach the doorand interact to proceed!";

			ss2 << "Health: " << playerHealth;


			player.getComponent<UILabel>().changePos(player.getComponent<TransformComponent>().position.x - camera.x, player.getComponent<TransformComponent>().position.y - camera.y);
			label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");
			label2.getComponent<UILabel>().SetLabelText(ss1.str(), "arial");
			player.getComponent<UILabel>().SetLabelText(ss2.str(), "arial");



		


			for (auto& c : enemies)
			{
				bool attacked = false;
				bool attackC = false;

				SDL_Rect enemyCol = c->getComponent<ColliderComponent>().collider;
				Vector2D enemyPos = c->getComponent<TransformComponent>().position;

				for (auto& b : colliders)
				{
					SDL_Rect cCol = b->getComponent<ColliderComponent>().collider;
					if (Collision::LRCol(cCol, enemyCol))
					{
						c->getComponent<TransformComponent>().position = { enemyPos.x , enemyPos.y - 3 };
					}

				}


				if (!(Collision::LRCol(playerCol, enemyCol) )) {
					if(enemyPos.x - playerPos.x < 100 ){
						if (playerPos.x + 30 > c->getComponent<TransformComponent>().position.x) {
							c->getComponent<TransformComponent>().velocity.x = 0.5;
							c->getComponent<SpriteComponent>().Play("Walk");
							c->getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_NONE;
						}
						if (playerPos.x + 30 < c->getComponent<TransformComponent>().position.x) {
							c->getComponent<TransformComponent>().velocity.x = -0.5;
							c->getComponent<SpriteComponent>().Play("Walk");
							
						}
					//if (playerPos.y - 30 < c->getComponent<TransformComponent>().position.y)
						//c->getComponent<TransformComponent>().velocity.y = -0.5;
					//if (playerPos.y - 30 > c->getComponent<TransformComponent>().position.y)
						//c->getComponent<TransformComponent>().velocity.y = 0.5;
					}
					



				}
				else {
					if (player.getComponent<SpriteComponent>().health > 0  && attackedTimer % 10 == 0) {
						
						player.getComponent<SpriteComponent>().attack(50);
						c->getComponent<SpriteComponent>().Play("Attack");
					}
					else if(player.getComponent<SpriteComponent>().health == 0) {
						player.getComponent<SpriteComponent>().Play("Dead");
						

						Mix_Music* music = Mix_LoadMUS("assets/death.mp3");
						//For playing audio effects;

						Mix_PlayMusic(music, 1);

						if (attackedTimer % 5 == 0)
							player.getComponent<SpriteComponent>().Play("Idle");
						if (attackedTimer % 10 == 0) {
							UILabel temp = UILabel(650, 320, "You have died :(", "arial", white);
							auto& ui(manager.addEntity());
							currLevel = 0;
						}
						//player.destroy();
						//currLevel = 0;
						

					}
					//c->getComponent<TransformComponent>().velocity.y = 0;
					c->getComponent<TransformComponent>().velocity.x = 0;
					//c->getComponent<SpriteComponent>().Play("Idle");
					
				}

				std::cout << "\ncurrAttack" << attackedTimer;
				attackedTimer++;



				

				if (Collision::LRCol(playerCol, enemyCol))
				{
					if (event.key.keysym.sym == SDLK_w) {
						Mix_PlayChannel(2, sound ,1);
						c->getComponent<SpriteComponent>().attack(100);
						if (c->getComponent<SpriteComponent>().health <= 0) {
							c->getComponent<SpriteComponent>().Play("Dead");
							c->destroy();
							enemyLeft--;
						}

					}
					player.getComponent<TransformComponent>().position.x = playerPos.x;
					c->getComponent<TransformComponent>().position.x = enemyPos.x + 1;
					//c->getComponent<TransformComponent>().position = enemyPos;
					std::cout << "Player ran into another";

				}


			}

			if (attackedTimer == 1000)
				attackedTimer = 0;

			for (auto& c : colliders)
			{
				SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
				//Vector2D id = c->getComponent<TransformComponent>().position;

				
				if (Collision::LRCol(cCol, playerCol))
				{
					std::cout << "\nX col:" << cCol.x << "y col: " << cCol.y;
					if (event.key.keysym.sym == SDLK_w && cCol.x == 4760 && cCol.y == 560) {
						finish = true;
						std::cout << "\nLevel finished";
					}
				   player.getComponent<TransformComponent>().position = {playerPos.x , playerPos.y - 3};
				}

			}

			for (auto& p : projectiles)
			{
				if (Collision::LRCol(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
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

		
		

}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		
		t->draw();
	}
	if (currLevel != 0) {

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

		for (auto& p : UI)
		{
			p->draw();
		}


		label.draw();
		label2.draw();
	}
	else {

		start->draw();
		settings->draw();
		exitB->draw();
		mouse.draw();
	}

	SDL_RenderPresent(renderer);
}


void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

