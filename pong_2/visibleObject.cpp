#include "visibleObject.h"
visibleObject::~visibleObject(){
}

visibleObject::visibleObject()
{
}
void visibleObject::update(double delta) {

}
void visibleObject::render() {
	for (int i = 0; i < texture.size(); i++) {
		COORD c = { int(prevX * 10), int(prevY * 10)+i };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		std::cout << std::flush << clearTexture[i];
	}
	for (int i = 0; i < texture.size(); i++) {
		COORD c = { int(x * 10), int(y * 10) + i };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		std::cout << std::flush << texture[i];
	}
}
