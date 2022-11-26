#include "Collision.h"
#include "ECS\ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
		

	if (
		recA.x + recA.w - 100 >= recB.x &&
		recB.x + recB.w - 100 >= recA.x &&
		recA.y + recA.h - 4 >= recB.y &&
		recB.y + recB.h - 4 >= recA.y
		)
	{
		return true;
	}

	return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		std::cout << colA.tag << " hit: " << colB.tag << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}