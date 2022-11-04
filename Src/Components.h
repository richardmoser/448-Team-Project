#pragma once
#include "ECS.h"

class PosistionComponent : public Component {

public:
	int x() { return xpos; }
	int y() { return ypos; }

	void init() override {

		xpos = 0;
		ypos = 0;

	}

	void update() override {

		xpos++;
		ypos++;

	}

	void setPos(int x, int y) {

		xpos = x;
		ypos = y;

	}

private:
	int xpos, ypos;


};