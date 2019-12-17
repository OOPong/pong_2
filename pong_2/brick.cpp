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

	int randIndex = rand() % 5;

	color = colors[randIndex];
	if (color == 79) {
		containPowerUp = true;
	}

	std::string tempstr = "";
	tempstr += no;
	for (int i = 0; i < length - 2; i++) {
		tempstr += ' ';
	}
	tempstr += no;

	for (int i = 0; i < height; i++) {
		clearTexture.push_back(std::string(length, ' '));
	}

	texture.push_back(std::string(length, no));
	for (int i = 0; i < height-2; i++) {
		texture.push_back(tempstr);
	}
	texture.push_back(std::string(length, no));
}
void brick::update(double d)
{
	if (_isActive) {
		if (breakTimer == 0) {
			blowUp();
		}
		else if (breakTimer != -1) {
			breakTimer -= 1;
		}

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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		for (int i = 0; i < texture.size(); i++) {
			COORD c = { round(x * 10) - marginX, round(y * 10) - marginY + i }; // -1 because ball coords is centered
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			std::cout << std::flush << texture[i];
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}

void brick::blowUp()
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

void brick::deactivate()
{
	if (breakTimer == -1) {
		breakTimer = 1;
	}
}

boundingRectangle brick::getBoundingRect()
{
	rect.x1 = (x - (double(length) / 20));
	rect.x2 = (x + (double(length) / 20));
	rect.y1 = (y - (double(height) / 20));
	rect.y2 = (y + (double(height) / 20));
	return rect;
}
