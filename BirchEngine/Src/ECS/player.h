#pragma once



class Player: public SpriteComponent{

private:

	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	//bool animated;
	int animIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	Player(std::string id, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 8, 100);
		Animation attack = Animation(2, 1, 100);
		Animation jump = Animation(3, 1, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);
		animations.emplace("Attack", attack);
		animations.emplace("Jump", jump);

		Play("Idle");

		setTex(id);
	}

	~Player()
	{

	}


	void update()
	{

		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x - Game::camera.x);
		destRect.y = static_cast<int>(transform->position.y - Game::camera.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}
#include "SpriteComponent.h"
};