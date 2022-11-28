#pragma once
#include <SDL.h>

class ColliderComponent;

class Collision
{
public:
	static bool LRCol(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};
