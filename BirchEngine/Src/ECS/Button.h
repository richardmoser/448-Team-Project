#include "SDL.h"
#include "Mouse.h"
#include "SDL_image.h"

class Button {
public:
	SDL_Texture* text;
	SDL_Texture* text2;
	SDL_Rect src, dest;
	bool isClicked = false;

	Button();


	void update(Mouse &mouse);
	void draw();
	void draw2();
};