#include "pad.h"

pad::pad()
{
	length = 10;
	height = 2;

	x = ((game_width/10)/2)-((double(length)/10)/2); // center the paddle
	y = 9;
	prevX = x;
	prevY = y;

	_velocity = 8;

	vx = 8;
	vy = 0;

	_isActive = true;
	_isStatic = false;

	texture.push_back(std::string(length, '='));
	texture.push_back(std::string(length, '='));

	clearTexture.push_back(std::string(length, ' '));
	clearTexture.push_back(std::string(length, ' '));

}

void pad::update(double d)
{
	prevX = x;
	prevY = y;

	double distance =  _velocity * d;
	if ((movement == direction::left) && ((x - (double(length) / 20) - distance) > 0.05)) {
		x = x - distance;
		vx = -1;
	}
	else if ( (movement == direction::right) && ( (x + (double(length) / 20) + distance) < ((game_width/10)-0.1)) ) {
		x = x + distance;
		vx = 1;
	}
	else {
		vx = 0;
	}
	movement = direction::none;

	rect.x1 = (x - (double(length) / 20));
	rect.x2 = (x + (double(length) / 20));
	rect.y1 = (y - (double(height) / 20));
	rect.y2 = (y + (double(height) / 20));
}

void pad::render()
{
	long marginX = length / 2;
	long marginY = 0;
	for (int i = 0; i < texture.size(); i++) {
		COORD c = { round(prevX * 10) - marginX, round(prevY * 10) - marginY + i }; //-1 because ball coords is centered
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		std::cout << std::flush << clearTexture[i];
	}
	for (int i = 0; i < texture.size(); i++) {
		COORD c = { round(x * 10) - marginX, round(y * 10) - marginY + i }; // -1 because ball coords is centered
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		std::cout << std::flush << texture[i];
	}
}

direction pad::getDirection()
{
	if (vx < 0) {
		return direction::left;
	}
	else if (vx > 0) {
		return direction::right;
	}
	return direction::none;
}
