//#include "Game.h"
#include "TextureManager.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <fstream>
#include <sstream>
#include <stdlib.h> 
#include "ECS/Button.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Renderer* Game::settRenderer = nullptr;
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
	this->tempW = width;
	this->tempH = height;

	
	int flags = 0;

	sound = Mix_LoadWAV("assets/sword.mp3");


	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024);

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

	assets->AddTexture("player", "assets/player_anims.png");
	assets->AddTexture("enemy", "assets/enemy_anims.png");
	assets->AddTexture("projectile", "assets/proj.png");



	assets->AddFont("arial", "assets/arial.ttf", 16);

	
		player.addComponent<TransformComponent>(60.0f, 300.0f, 32, 32, 4);
		player.addComponent<SpriteComponent>("player", true);
		player.addComponent<KeyboardController>();
		player.getComponent<TransformComponent>().velocity.y = 0.75f;
		player.addComponent<ColliderComponent>("player", player.getComponent<TransformComponent>().position.x, player.getComponent<TransformComponent>().position.y, 1);//, player.getComponent<SpriteComponent>().srcRect.h, player.getComponent<SpriteComponent>().srcRect.w);
		player.addGroup(groupPlayers);
		player.addComponent<UILabel>(10, 400, "", "arial", white);


	
	label.addComponent<UILabel>(0, 0, "", "arial", white);
	label2.addComponent<UILabel>(0, 0, "", "arial", white);

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

		auto& enemy(manager.addEntity());
		enemy.addComponent<TransformComponent>(x, y, 32, 32, 4);
		enemy.getComponent<TransformComponent>().velocity.y = 0.75f;
		enemy.addComponent<SpriteComponent>("enemy", true);
		//enemy.addComponent<HitboxComponent>(&playerPos, &enemyPos);
		enemy.addComponent<ColliderComponent>("enemy", enemy.getComponent<TransformComponent>().position.x, enemy.getComponent<TransformComponent>().position.y, 1);//, enemy.getComponent<SpriteComponent>().srcRect.h, enemy.getComponent<SpriteComponent>().srcRect.w);
		enemy.addGroup(groupEnemies);
		SDL_Color white = { 255, 255, 255, 255 };
		enemy.addComponent<UILabel>(500, 400, "", "arial", white);
		enemy.getComponent<SpriteComponent>().health = tHealth;
		enemyLeft++;


}

Button* start;
Button* settings;
Button* exitB;

Button* fullscreenB;
Button* backB;
Button* soundB;
Button* menu;
Button* restart;

Mouse mouse;
bool createdWindow = false;


void Game::setting() {


	SDL_Texture* rtexture;
	SDL_Rect destination;
	



	if (!createdWindow) {
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{
			if(fullScreen == SDL_FALSE && createdWindow)
				settWindow = SDL_CreateWindow("Settings", 0, 0, tempW, tempH, 0);
			else
				settWindow = SDL_CreateWindow("Settings", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, tempW, tempH, 0);
			settRenderer = SDL_CreateRenderer(settWindow, 00, 0);
			if (settRenderer)
			{
				//SDL_SetRenderDrawColor(settRenderer, 0, 0, 0, 0);
			}

			SDL_SetWindowBordered(settWindow, SDL_FALSE);
		}
		//SDL_Event e;
		//SDL_PollEvent(&e);
		//SDL_CaptureMouse(SDL_TRUE);
		//Mouse newMouse;
		

		
		
		//SDL_RenderCopy(settRenderer, rtexture, NULL, &destination);
		createdWindow = true;
		
		fullscreenB = new Button;
		soundB = new Button;
		backB = new Button;
		menu = new Button;
		//mouse = new Mouse;
		//backB = new Button;

		
	}

	SDL_RenderClear(settRenderer);
	
	fullscreenB->src.y = 150;
	fullscreenB->dest.x = tempW / 2 - fullscreenB->dest.w / 2;
	fullscreenB->dest.y = tempH / 2 - fullscreenB->dest.h / 2 - 50;

	soundB->src.y = 250;
	soundB->dest.x = tempW / 2 - soundB->dest.w / 2;
	soundB->dest.y = tempH / 2 - soundB->dest.h / 2 + 50;

	backB->src.y = 200;
	backB->dest.x = (tempW / 2) - (backB->dest.w / 2 );
	backB->dest.y = (tempH / 2) - (backB->dest.h / 2 ) + 150;

	menu->src.y = 290;
	menu->dest.x = (tempW / 2) - (menu->dest.w / 2);
	menu->dest.y = (tempH / 2) - (menu->dest.h / 2) + 300;

			
			destination.x = 0;
			destination.y = 0;

			destination.w = tempW;
			destination.h = tempH;

			SDL_Surface* rainbow = IMG_Load("assets/Settings.png");
			rtexture = SDL_CreateTextureFromSurface(settRenderer, rainbow);
			SDL_FreeSurface(rainbow);
			SDL_RenderCopy(settRenderer, rtexture, NULL, &destination);
			
			
			
			

			
			fullscreenB->update(mouse);
			soundB->update(mouse);
			backB->update(mouse);
			menu->update(mouse);
			mouse.update();
			
			fullscreenB->draw2();
			soundB->draw2();
			backB->draw2();
			menu->draw2();
			//newMouse.draw2();
			mouse.draw2();

			

			if (event.button.button == SDL_BUTTON_LEFT && (event.type == SDL_MOUSEBUTTONDOWN )){
				if (fullscreenB->isClicked) {
					if (fullScreen == SDL_FALSE) {
						fullScreen = SDL_TRUE;
						tempW = width;
						tempH = height;
						SDL_SetWindowSize(window, tempW, tempH);
						SDL_SetWindowSize(settWindow, tempW, tempH);
						SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
						SDL_SetWindowPosition(settWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
						
					}
					else {
						fullScreen = SDL_FALSE;

						SDL_GetDesktopDisplayMode(0, &DM);
						//auto tt = DM.w;
						tempW = DM.w;
						tempH = DM.h;
					
						SDL_SetWindowSize(window, DM.w, DM.h);
						SDL_SetWindowSize(settWindow, DM.w, DM.h);
						SDL_SetWindowPosition(window, 0, 0);
						SDL_SetWindowPosition(settWindow, 0, 0);
					}

					SDL_SetWindowBordered(window, fullScreen);
					std::cout << "\nFullscreen";
				}

				if (menu->isClicked) {
					settingWindow = false;
					createdWindow = false;
					SDL_DestroyWindow(settWindow);
					SDL_DestroyRenderer(settRenderer);
					currLevel = 0;
					updateMap(currLevel);
				}

				if (soundB->isClicked) {
					std::cout << "\n sound has been clicked";
					if (muted) {
						Mix_Music* music = Mix_LoadMUS("assets/the_rainbow_train.mp3");
						Mix_PlayMusic(music, 10);
						muted = false;
					}
					else {
						Mix_HaltMusic();
						muted = true;
					}
				}

				if (backB->isClicked) {
					settingWindow = false;
					createdWindow = false;
					SDL_DestroyWindow(settWindow);
					SDL_DestroyRenderer(settRenderer);
					
				}

				//manager.update();

				

		

			}
			SDL_RenderPresent(settRenderer);
	//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);


}

void Game::updateMap(int level) {
	
	
	finish = false;

	SDL_RenderClear(renderer);
	
	if (player.getComponent<SpriteComponent>().health == 0 || currLevel == 0 && !muted) {
		Mix_Music* music = Mix_LoadMUS("assets/the_rainbow_train.mp3");
		Mix_PlayMusic(music, 10);
	}

	player.getComponent<TransformComponent>().position = { 60.0f, 488.0f };
	player.getComponent<SpriteComponent>().health = 100;
	player.getComponent<SpriteComponent>().Play("Idle");

	if (level < myLevels.size()) {
		
		enemyLeft = 0;


		
		 //For playing audio effects;

		


		

		while (enemies.size() != 0)
			enemies.pop_back();

		while (tiles.size() != 0)
		tiles.pop_back();

		while (colliders.size() != 0)
			colliders.pop_back();
		
		if (level == 1) {
			SDL_SetRenderDrawColor(renderer, 0, 221, 202, 255);
		}
		
		if (level == 2) {
			SDL_SetRenderDrawColor(renderer, 234, 221, 202, 255);
		}

		if (level == 3) {
			SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
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

		
		//isRunning = false;

		assets->AddTexture(tempString3, tempString.c_str());
		//myFile.close();
		map = new Map(tempString3, scale, pngW);
		//ecs implementation
		if (level == 4) {
			tw = 160;
			th = 90;
		}
		map->LoadMap(tempString2, tw, th);
		mapLoaded = true;
		//manager.update();5

		

		

		
	}
	else {
		isRunning = false;
	}
}



//Button* menu;

void Game::update(std::string FPS)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p) {
		currLevel++;
		updateMap(currLevel);
	}


	restart = new Button;
	menu = new Button;


	restart->src.y = 330;
	restart->dest.x = tempW / 2 - restart->dest.w / 2;
	restart->dest.y = tempH / 2 - restart->dest.h / 2;

	menu->src.y = 280;
	menu->dest.x = tempW / 2 - menu->dest.w / 2;
	menu->dest.y = tempH / 2 - menu->dest.h / 2 + 150;



	menu->update(mouse);
	restart->update(mouse);
	
	//player.getComponent<TransformComponent>().velocity.y = 0.5;
	label.getComponent<UILabel>().changePos(0 - camera.x, 300 - camera.y);
	mouse.update();
	if (!settingWindow) {
		if (event.key.keysym.sym == SDLK_ESCAPE)
			settingWindow = true;
		int settingNum = 0;

		std::cout << "\nCurr level" << currLevel;

		


		if (currLevel == 0) {
			if (!mapLoaded) {
				updateMap(currLevel);
			}
			start = new Button;
			settings = new Button;
			exitB = new Button;
			start->src.y = 0;
			start->dest.x = tempW / 2 - start->dest.w / 2;
			start->dest.y = (tempH / 2) - (start->dest.h / 2);

			settings->src.y = 50;
			settings->dest.x = tempW / 2 - start->dest.w / 2;
			settings->dest.y = (tempH / 2) - (start->dest.h / 2) + 150;

			exitB->src.y = 100;
			exitB->dest.x = tempW / 2 - start->dest.w / 2;
			exitB->dest.y = (tempH / 2) - (start->dest.h / 2) + 300;

		

			start->update(mouse);
			settings->update(mouse);
			exitB->update(mouse);
			//mouse->update();

			//mouse.draw();
		


			manager.update();
			//manager.refresh();

			if (event.button.button == SDL_BUTTON_LEFT && (event.type == SDL_MOUSEBUTTONDOWN)) {
				if (start->isClicked) {
					currLevel++;
					mapLoaded = false;
				}

				if (settings->isClicked && settingNum == 0) {
					settingWindow = true;
					//setting();
				}

				if (exitB->isClicked) {
					isRunning = false;
				}
			}

		}
		else {

			if (currLevel > myLevels.size())
				isRunning = false;



			if (!mapLoaded) {
				//myLevels[currLevel] = true;

				updateMap(currLevel);
				if (currLevel == 1)
					map1 = true;

			}

			if (enemyLeft <= 0 && finish) {
				if (map1)
					currLevel++;
				mapLoaded = false;
				finish = false;
			}


			for (auto& c : enemies) {
				std::stringstream ss1, ss3;
				enemyPos = c->getComponent<TransformComponent>().position;
				int enemyHealth = c->getComponent<SpriteComponent>().health;
				ss1 << "Enemy position: " << enemyPos << ", velocity: " << c->getComponent<TransformComponent>().velocity;
				ss3 << "Enemy Health: " << enemyHealth;
				c->getComponent<UILabel>().changePos(c->getComponent<TransformComponent>().position.x - camera.x, c->getComponent<TransformComponent>().position.y - camera.y);
				c->getComponent<UILabel>().SetLabelText(ss3.str(), "arial");
			}


			SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
			Vector2D playerPos = player.getComponent<TransformComponent>().position;

			manager.update();
			manager.refresh();




			int playerHealth = player.getComponent<SpriteComponent>().health;


			std::stringstream ss1, ss2, ss, ss3;
			if (currLevel == 1)
				ss << "Instructions:\nKeybinds -  \nA: Move Left \nD: Move Right\nSPACE : Jump\nW: Interact / Attack\nESC : open the menu\nObjective - Deafeat the " << enemyLeft << " enemies, then reach the door and interact to proceed!";

			ss2 << "Health: " << playerHealth;

			ss1 << FPS;


			player.getComponent<UILabel>().changePos(player.getComponent<TransformComponent>().position.x - camera.x, player.getComponent<TransformComponent>().position.y - camera.y);
			label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");
			label2.getComponent<UILabel>().SetLabelText(ss1.str(), "arial");
			player.getComponent<UILabel>().SetLabelText(ss2.str(), "arial");






			for (auto& c : enemies)
			{

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


				if (abs(enemyPos.x - (playerPos.x)) >= 30){//!(Collision::LRCol(playerCol, enemyCol))) {
					if (enemyPos.x - playerPos.x < 200) {
						if (playerPos.x + 30 > c->getComponent<TransformComponent>().position.x) {
							c->getComponent<TransformComponent>().velocity.x = 0.5;
							c->getComponent<SpriteComponent>().Play("Walk");
							c->getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_NONE;

						}
						if (playerPos.x + 30 < c->getComponent<TransformComponent>().position.x) {
							c->getComponent<TransformComponent>().velocity.x = -0.5;
							c->getComponent<SpriteComponent>().Play("Walk");
							c->getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_HORIZONTAL;


						}
	
					}




				}
				else {

					if (player.getComponent<SpriteComponent>().health > 0 && attackedTimer % 10 == 0 && (playerPos.y - 10 <= c->getComponent<TransformComponent>().position.y  && playerPos.y + 10 >= c->getComponent<TransformComponent>().position.y) ){

						player.getComponent<SpriteComponent>().attack(5);
						Mix_PlayChannel(1, sound, 1);
						c->getComponent<SpriteComponent>().Play("Attack");
					}
					else if (player.getComponent<SpriteComponent>().health == 0) {
						Mix_Music* music = Mix_LoadMUS("assets/death.mp3");
						Mix_PlayMusic(music, 1);

						player.getComponent<SpriteComponent>().Play("Dead");

						
						
						//For playing audio effects;

						

						

						if (attackedTimer % 5 == 0) {
							UILabel temp = UILabel(650, 320, "You have died :(", "arial", white);
							temp.draw();

						

							

							if (event.button.button == SDL_BUTTON_LEFT ) {
								if (menu->isClicked) {
									currLevel = 0;
									mapLoaded = false;
									updateMap(currLevel);

								}
								if (restart->isClicked) {
									mapLoaded = false;
									updateMap(currLevel);
									player.getComponent<TransformComponent>().position = { 60.0f, 488.0f };
								}
							}

							finish = false;
							
						}
						//player.destroy();
						//currLevel = 0;


					}
					//c->getComponent<TransformComponent>().velocity.y = 0;
					c->getComponent<TransformComponent>().velocity.x = 0;
					//c->getComponent<SpriteComponent>().Play("Idle");

				}

				attackedTimer++;

				if (Collision::LRCol(playerCol, enemyCol)) {
					player.getComponent<TransformComponent>().position.x = playerPos.x;
					//c->getComponent<TransformComponent>().position.x = enemyPos.x + 1;
					//c->getComponent<TransformComponent>().position = enemyPos;
					
				}


			

				if (abs(player.getComponent<TransformComponent>().position.x - (enemyPos.x)) <= 60)// && (abs(enemyPos.x - player.getComponent<TransformComponent>().position.x) <= 5)) //&& 0 <= enemyPos.x - player.getComponent<TransformComponent>().position.x >= 0))
				{
	

					if (event.key.keysym.sym == SDLK_w) {
						Mix_PlayChannel(1, sound, 1);
						c->getComponent<SpriteComponent>().attack(20);
						if (c->getComponent<SpriteComponent>().health <= 0) {
							c->getComponent<SpriteComponent>().Play("Dead");
							c->destroy();
							enemyLeft--;
						}

					}


				}


			}

			if (attackedTimer == 1000)
				attackedTimer = 0;

			for (auto& c : colliders)
			{
				SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
				//Vector2D id = c->getComponent<TransformComponent>().position;

				if (Collision::LRCol(playerCol, cCol)) {
					//if (Collision::RCol(playerCol, cCol))
						//player.getComponent<TransformComponent>().position.x = playerPos.x;
					//if(Collision::BCol(playerCol,cCol))
						//player.getComponent<TransformComponent>().position.y = playerPos.y;
					player.getComponent<TransformComponent>().position.y = playerPos.y - 3;
					player.getComponent<TransformComponent>().position.x = playerPos.x;
				}
				/*
				5
				if (Collision::LCol(playerCol, cCol) && !Collision::BCol(playerCol, cCol))
				{
					player.getComponent<TransformComponent>().position.x = playerPos.x + 1;
				   //player.getComponent<TransformComponent>().velocity.y = -2;
				   //player.getComponent<TransformComponent>().position.x = playerPos.x;
				}
				if (Collision::RCol(playerCol, cCol) && !Collision::BCol(playerCol, cCol))
				{
					player.getComponent<TransformComponent>().position.x = playerPos.x - 0.1;
					//player.getComponent<TransformComponent>().velocity.y = -2;
					//player.getComponent<TransformComponent>().position.x = playerPos.x;
				}
				if (Collision::TCol(playerCol, cCol) && !Collision::BCol(playerCol, cCol))
				{
					player.getComponent<TransformComponent>().position.y = playerPos.y;
					//player.getComponent<TransformComponent>().velocity.y = -2;
					//player.getComponent<TransformComponent>().position.x = playerPos.x;
				}
				if (Collision::BCol(playerCol, cCol))
				{
					player.getComponent<TransformComponent>().position.y = playerPos.y;
					//player.getComponent<TransformComponent>().velocity.y = -2;
					//player.getComponent<TransformComponent>().position.x = playerPos.x;
				}
				*/





				if (event.key.keysym.sym == SDLK_w && cCol.x == 4760 && cCol.y == 560 && cCol.x - player.getComponent<TransformComponent>().position.x <= 100) {
					finish = true;
				}

			}

			for (auto& p : projectiles)
			{
				if (Collision::LRCol(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
				{
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
		
	
}

void Game::render()
{
	if (!settingWindow) {
		SDL_RenderClear(renderer);
		//Draw rainbow
		SDL_Surface* rainbow = IMG_Load("assets/rainbow.png");
		SDL_Texture* rtexture = SDL_CreateTextureFromSurface(renderer, rainbow);
		SDL_FreeSurface(rainbow);

		SDL_Rect destination;
		destination.x = camera.x / -15;//- (player.getComponent<TransformComponent>().position.x / 2)  ;
		destination.y = camera.y;
		destination.w = tempW * 1.3f;
		destination.h = tempH * 1.25f;

		if (currLevel != 0)
			SDL_RenderCopy(renderer, rtexture, NULL, &destination);

		for (auto& t : tiles)
		{

			t->draw();
		}
		if (currLevel != 0) {


			for (auto& c : colliders)
			{
				int w, h;
				SDL_GetWindowSize(window, &w,
					&h);
				if ((camera.x + w) - c->getComponent<TransformComponent>().position.x >= 0 && c->getComponent<TransformComponent>().position.x - (camera.x - 100) > 0) {
					c->draw();
				}
				//std::cout << "\nCollider has been drawn";
			}
			if (currLevel != 4) {
				for (auto& p : players)
				{
					int w, h;
					SDL_GetWindowSize(window, &w,
						&h);
					if ((camera.x + w) - p->getComponent<TransformComponent>().position.x >= 0 && p->getComponent<TransformComponent>().position.x - (camera.x - 100) > 0)
						p->draw();

					//std::cout << "\nPlayer has been drawn";
				}
			}

			for (auto& e : enemies)
			{
				int w, h;
				SDL_GetWindowSize(window, &w,
					&h);
				if ((camera.x + w) - e->getComponent<TransformComponent>().position.x >= 0 && e->getComponent<TransformComponent>().position.x - (camera.x - 100) > 0) {
					e->draw();
				
				}
				//std::cout << "\nEnemy has been drawn" << e->getComponent<TransformComponent>().position.x << " " << w;
			}

			for (auto& p : projectiles)
			{
				p->draw();
			}

			for (auto& p : UI)
			{
				p->draw();
			}


			
			label2.draw();
			label.draw();

			if (player.getComponent<SpriteComponent>().health <= 0 ) {
				menu->draw();
				restart->draw();

			}
			
		}
		else {

			start->draw();
			settings->draw();
			exitB->draw();
			mouse.draw();
		}
		
		SDL_RenderPresent(renderer);

	
	}
}


void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

