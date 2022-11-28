#pragma once

#include "ECS.h"
#include "../Vector2D.h"
#include "../Game.h"
#include "../TextureManager.h"

class TileComponent : public Component
{
public:

	SDL_Texture * texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;
	std::string tid;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, int tHeight, int tscale, std::string id)
	{
		texture = Game::assets->GetTexture(id);
		tid = id;
		srcRect.x = srcX;
		srcRect.y = srcY;
		//srcRect.w = tWidth;
		srcRect.h = srcRect.w = tHeight;
		position.x = static_cast<float>(xpos);
		position.y = static_cast<float>(ypos);
		destRect.w = tHeight * tscale;
		destRect.h = tHeight * tscale;
	}

	void update() override
	{
		destRect.x = static_cast<int>(position.x - Game::camera.x);
		destRect.y = static_cast<int>(position.y - Game::camera.y);
	}
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};