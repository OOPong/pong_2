#include "visibleObject.h"
visibleObject::~visibleObject(){
}
/*
void visibleObject::render() {
	COORD c;

	//clear previous block
	//always begin drawing at top left corner
	c.X = prevX;
	c.Y = prevY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	std::cout << std::string(texture.length(), ' ');

	//print this block
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);	//chọn màu cho bóng (màu vàng)
	std::cout << texture;											// in quả bóng
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	prevX = x;
	prevY = y;
}
*/

visibleObject::visibleObject()
{
	vx = 0;
	vy = 0;
	_isActive = true;
	_isStatic = false;
}
void visibleObject::update() {

}
void visibleObject::render() {
	COORD c = { int(x*10), int(y*10) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	std::cout << std::flush << texture;
	//printf_s(texture.c_str());
}
