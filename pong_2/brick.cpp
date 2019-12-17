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

<<<<<<< HEAD
	for (int i = 0; i < height; i++) {
		texture.push_back(std::string(length, no));
		clearTexture.push_back(std::string(length, ' '));
	}
=======
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
>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6
}
void brick::update(double d)
{
	if (_isActive) {
<<<<<<< HEAD
=======
		if (breakTimer == 0) {
			blowUp();
		}
		else if (breakTimer != -1) {
			breakTimer -= 1;
		}

>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6
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
<<<<<<< HEAD
=======
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6
		for (int i = 0; i < texture.size(); i++) {
			COORD c = { round(x * 10) - marginX, round(y * 10) - marginY + i }; // -1 because ball coords is centered
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			std::cout << std::flush << texture[i];
		}
<<<<<<< HEAD
	}
}

void brick::deactivate()
=======
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}

void brick::blowUp()
>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6
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

<<<<<<< HEAD
=======
void brick::deactivate()
{
	if (breakTimer == -1) {
		breakTimer = 1;
	}
}

>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6
boundingRectangle brick::getBoundingRect()
{
	rect.x1 = (x - (double(length) / 20));
	rect.x2 = (x + (double(length) / 20));
	rect.y1 = (y - (double(height) / 20));
	rect.y2 = (y + (double(height) / 20));
	return rect;
}
