#pragma once

#include "ECS.h"
#include "../AssetManager.h"
#include "../Game.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel : public Component
{
public:
	UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour) :
		labelText(text), labelFont(font), textColour(colour)
	{
		position.x = xpos;
		position.y = ypos;

		SetLabelText(labelText, labelFont);
	}
	~UILabel()
	{}

	void SetLabelText(std::string text, std::string font)
	{
		SDL_Color back = { 0,0,0,0 };
		SDL_Surface* surf = TTF_RenderText_LCD_Wrapped(Game::assets->GetFont(font), text.c_str(), textColour, back, 0);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void changePos(int x, int y) {
		position.x = x;
		position.y = y;
	}

	void draw() override
	{
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
	}

private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColour;
	SDL_Texture* labelTexture;
};
