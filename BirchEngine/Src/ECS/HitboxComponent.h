#pragma once

#include <SDL.h>
#include "Components.h"

class HitboxComponent : public Component {
public:
	Vector2D *hitBox;
	Vector2D *otherBox;
	int oBoxHealth;

	
    HitboxComponent();
	
	HitboxComponent(Vector2D *hBox, Vector2D *oBox) {
		hitBox = hBox;
		otherBox = oBox;
		oBoxHealth = 100;
	}
	
	/*
	HitboxComponent(SDL_Rect hBox, SDL_Rect oBox, int xpos, int ypos, int size) {
		
		//thisTag = tag;
		hitBox.x = xpos;
		hitBox.y = ypos;
		hitBox.h = hitBox.w = size;
	}
	*/

	void damage() {
		std::cout << hitBox->x;
		if ((hitBox->x >= otherBox->x - 5 && hitBox->x <= otherBox->x + 5) && (hitBox->y >= otherBox->y - 5 && hitBox->y <= otherBox->y + 5)) {
			oBoxHealth -= 10;
			std::cout << "\n" << oBoxHealth;
		}
	}

	void update() {
		if ((hitBox->x >= otherBox->x - 5 && hitBox->x <= otherBox->x + 5) && (hitBox->y >= otherBox->y - 5 && hitBox->y <= otherBox->y + 5)) {
			std::cout << "\nPlayer detected  " << hitBox->x << " == " << otherBox->x;
		}
	}


};