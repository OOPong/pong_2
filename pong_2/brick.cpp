#include "brick.h"
brick::brick(float xin, float yin, char no) {
	length = 10;
	height = 4;

	x = xin;
	y = yin;

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
void brick::update(double d)
{
	if (_isActive) {
		rect.x1 = (x - (double(length) / 20));
		rect.x2 = (x + (double(length) / 20));
		rect.y1 = (y - (double(height) / 20));
		rect.y2 = (y + (double(height) / 20));
	}
}

void brick::render()
{
	if (_isActive) {
		long marginX = length / 2;
		long marginY = height / 2;
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
}

void brick::deactivate()
{
	long marginX = length / 2;
	long marginY = height / 2;
	for (int i = 0; i < texture.size(); i++) {
		COORD c = { round(prevX * 10) - marginX, round(prevY * 10) - marginY + i }; //-1 because ball coords is centered
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		std::cout << std::flush << clearTexture[i];
	}
	_isActive = false;
}

boundingRectangle brick::getBoundingRect()
{
	rect.x1 = (x - (double(length) / 20));
	rect.x2 = (x + (double(length) / 20));
	rect.y1 = (y - (double(height) / 20));
	rect.y2 = (y + (double(height) / 20));
	return rect;
}
