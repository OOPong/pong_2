#include "brick.h"
brick::brick(float x, float y, char no) {
	length = 10;
	height = 4;

	x = ((game_width / 10) / 2) - ((double(length) / 10) / 2); // center the paddle
	y = 9;

	prevX = x;
	prevY = y;

	vx = 8;
	vy = 0;

	_isActive = true;
	_isStatic = true;

	for (int i = 0; i < height; i++) {
		texture.push_back(std::string(length, no));
		clearTexture.push_back(std::string(length, ' '));
	}
}