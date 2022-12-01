#include "ECS/Button.h"


Button::Button() {
	static SDL_Texture* t = IMG_LoadTexture(Game::renderer, "assets/buttons.png");
	text2 = IMG_LoadTexture(Game::settRenderer, "assets/buttons.png");
	
	text = t;


	src.h = src.w = 50;
	src.x = 0;

	dest.h = dest.w = 150;

}


void Button::update(Mouse &mouse) {


	if (SDL_HasIntersection(&dest, &mouse.point)) {
		isClicked = true;
		src.x = 50;

	}
	else {
		isClicked = false;
		src.x = 0;
	}
}

void Button::draw() {
	SDL_RenderCopy(Game::renderer, text, &src, &dest);
}

void Button::draw2() {
	SDL_RenderCopy(Game::settRenderer, text2, &src, &dest);
}