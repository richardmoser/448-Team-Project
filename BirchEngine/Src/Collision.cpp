#include "Collision.h"
#include "ECS\ColliderComponent.h"

bool Collision::LRCol(const SDL_Rect& recA, const SDL_Rect& recB)
{
		

	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		)
	{
		return true;
	}

	return false;
}

bool Collision::RCol(const SDL_Rect& recA, const SDL_Rect& recB) {
	SDL_Rect tempRecB = recB;
	if (recA.x + recA.w >= recB.x && (recA.y >= (tempRecB.h + tempRecB.y)) / 2) {
		std::cout << "\nRecA.x " << recB.x << " recB.x" << recB.x + recB.h;
		return true;
	}
	else
		false;
}

bool Collision::LCol(const SDL_Rect& recA, const SDL_Rect& recB) {
	if (recB.x >= recA.x)
		return true;
	else
		false;
}

bool Collision::TCol(const SDL_Rect& recA, const SDL_Rect& recB) {
	if (recA.y + recA.h >= recB.y)
		return true;
	else
		false;
}

bool Collision::BCol(const SDL_Rect& recA, const SDL_Rect& recB) {
	
		if (recA.y > recB.y)
			return true;
		else
			false;
}


bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (LRCol(colA.collider, colB.collider))
	{
		std::cout << colA.tag << " hit: " << colB.tag << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}