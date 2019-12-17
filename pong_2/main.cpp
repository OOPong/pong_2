<<<<<<< HEAD
#include "game.h"
int main() {
=======
#include "config.h"
#include "game.h"
int main() {
	std::srand(std::time(nullptr));
>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6
	game::loop();
	return 0;
}