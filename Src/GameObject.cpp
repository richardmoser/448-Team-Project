#include "GameObject.h"
#include "TextureManager.h"
#include <iostream>
#include <math.h>

GameObject::GameObject(const char* textureSheet, int x, int y) {

	objTexture = TextureManager::LoadTexture(textureSheet);

	xpos = x;
	ypos = y;
	//srcRect.x = 0;
	//srcRect.y = 0;
	srcRect.h = 62;
	srcRect.w = 50;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;


}

void GameObject::Update() {
	SDL_Event event;
	SDL_PollEvent(&event);

	destRect.x = xpos;
	destRect.y = ypos;


	switch (event.key.keysym.sym) {
	case SDLK_d:
		xpos += 100;
		break;
	case SDLK_a:
		xpos -= 50;
		break;
	case SDLK_s:
		ypos += 100;
		break;
	case SDLK_w:
		ypos -= 100;
		break;
	default:
		break;
	}

}

void GameObject::Render() {
	SDL_RenderCopy(game::renderer, objTexture, &srcRect, &destRect);
}