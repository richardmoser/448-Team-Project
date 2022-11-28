#pragma once

#include "../Game.h"
#include "SDL_timer.h"
#include "ECS.h"
#include "Components.h"
#include "HitboxComponent.h"
#include "../Map.h"
#include <ctime>
#include <stdlib.h> 
#include <time.h>

class KeyboardController : public Component
{
public:
	Game* myGame;
	HitboxComponent *box;
	Map *pause;
	TransformComponent *transform;
	SpriteComponent *sprite;
	SDL_Window* window;
	Vector2D gravity{ 0,-2 };
	float prevTime, currTime, dt;
	
	
	//Map *pause;
	float getTime() {
		return time(0);
	}


	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		
		if (entity->hasComponent<HitboxComponent>())
			std::cout << "Has Hitbox";
		else
			std::cout << "does not have component";
	}

	void update() override
	{
		/*
		window;//SDL_CreateWindow("Pause", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
		myRender = SDL_CreateRenderer(window, 00, 0);
		if (myRender)
		{
			SDL_SetRenderDrawColor(myRender, 255, 255, 255, 255);
		}
		*/

		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				sprite->Play("Attack");
				break;
	
			case SDLK_a + SDLK_SPACE:
				transform->velocity.x = -2;
				//transform->velocity.y = 0;
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				sprite->Play("Jump");
				for (float i = 1; i <= 100; i++) {
					transform->velocity.y = -1;
				}
				break;
			case SDLK_a:
				transform->velocity.x = -2;
				//transform->velocity.y = 0;
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;

			case SDLK_d + SDLK_SPACE:
				transform->velocity.x = 2;
				//transform->velocity.y = 0;
				sprite->Play("Walk");
				sprite->Play("Jump");
				for (float i = 1; i <= 100; i++) {
					transform->velocity.y = -1;
				}
				break;

			case SDLK_d:
				transform->velocity.x = 2;
				//transform->velocity.y = 0;
				sprite->Play("Walk");
				break;
			case SDLK_f:
				sprite->Play("Attack");
				break;
			case SDLK_SPACE:
				
				
				sprite->Play("Jump");
				for (float i = 1; i <= 100; i++) {
					transform->velocity.y = -1;
				}
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			default:
				break;
			}

		

		}
	
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				sprite->Play("Idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_a + SDLK_SPACE:
				transform->velocity.x = 0;
				transform->velocity.y = 1;
				sprite->Play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				break;
			case SDLK_d + SDLK_SPACE:
				transform->velocity.x = 0;
				transform->velocity.y = 1;
				sprite->Play("Idle");
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			case SDLK_f:
				sprite->Play("Idle");
				break;
			case SDLK_SPACE:
				sprite->Play("Idle");
				transform->velocity.y = 1;
				transform->velocity.x = 0;
				break;
				
			default:
				break;
			}
		}
	}
};