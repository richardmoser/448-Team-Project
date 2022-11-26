#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "HitboxComponent.h"
#include "../Map.h"

class KeyboardController : public Component
{
public:
	HitboxComponent *box;
	Map *pause;
	TransformComponent *transform;
	SpriteComponent *sprite;
	SDL_Renderer* myRender;
	SDL_Window* window;
	
	//Map *pause;


	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		
		if (entity->hasComponent<HitboxComponent>())
			std::cout << "Has Hitbox";
		else
			std::cout << "does not have component";

		box = &entity->getComponent<HitboxComponent>();
		pause = new Map("terrain", 3, 32);
		//ecs implementation
		pause->LoadMap("assets/map2.map", 25, 20);
	}

	void update() override
	{
		/*
		window;//SDL_CreateWindow("Pause", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
		myRender = SDL_CreateRenderer(window, -1, 0);
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
				transform->velocity.y = -1;
				sprite->Play("Walk");
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->Play("Walk");
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->Play("Walk");
				break;
			case SDLK_f:
				sprite->Play("Attack");

				break;
			case SDLK_SPACE:
				sprite->Play("Jump");
				transform->velocity.y = -1;
				break;
			case SDLK_ESCAPE:
				std::cout << "Changing map";
				Game::changeMap(pause);
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
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_ESCAPE:
				//Game::isRunning = false
				
				break;
			case SDLK_f:
				sprite->Play("Idle");
				break;
			case SDLK_SPACE:
				sprite->Play("Idle");
				transform->velocity.y = 1;
				transform->velocity.y = 0;
				
				break;
			default:
				break;
			}
		}
	}
};