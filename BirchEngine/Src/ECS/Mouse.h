
#include "Game.h"

class Mouse {
public:
	
	SDL_Texture* tex;
	SDL_Texture* tex2;
	SDL_Rect rect, point;

	Mouse() {
		tex = IMG_LoadTexture(Game::renderer, "assets/pointer.png");
		tex2 = IMG_LoadTexture(Game::settRenderer, "assets/pointer.png");
		rect.w = rect.h = 35;
		point.h = point.w = 1;
		//SDL_ShowCursor(false);
	}
	//virtual ~Mouse();

	void update() {
		SDL_GetMouseState(&rect.x, &rect.y);
		point.x = (int)rect.x;
		point.y = (int)rect.y;
	}

	void draw() {
		std::cout << "\n" << SDL_RenderCopy(Game::renderer, tex, NULL, &point);
	}

	void draw2() {
		std::cout << "\n" << SDL_RenderCopy(Game::settRenderer, tex2, NULL, &point);
	}
};