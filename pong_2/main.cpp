#include "config.h"
#include "game.h"
int main() {
	std::srand(std::time(nullptr));
	game::loop();
	return 0;
}