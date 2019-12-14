#include "game.h"
using namespace std::chrono_literals;

void game::borderSetup(game::game_state current_state)
{
	//change font size
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = int(game_width / 15);                   // Width of each character in the font
	cfi.dwFontSize.Y = int(game_height / 15);                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(current_state.stdHandle, FALSE, &cfi);

	//set console
	HWND hwnd = GetConsoleWindow();
	RECT rect = { 100, 300, 800, 975 };
	MoveWindow(hwnd, rect.top, rect.left, rect.bottom - rect.top, rect.right - rect.left, TRUE);

	/*
	//hide cursor
	CONSOLE_CURSOR_INFO ConCurInf;
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = false;
	SetConsoleCursorInfo(current_state.stdHandle, &ConCurInf);
	*/

	//in ra khung bàn chơi
	SetConsoleTextAttribute(current_state.stdHandle, 15);
	for (int i = 0; i < game_width - 1; ++i) {
		std::cout << '-';
	}

	std::cout << std::endl;

	for (int i = 0; i < game_height - 2; ++i) {
		std::cout << "|";
		gotoxy(game_width - 2, i);
		std::cout << "|" << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < game_width - 1; ++i) {
		std::cout << '=';
	}
}

bool game::handleEvents(game_state* state) {
	// poll for events
	if (GetAsyncKeyState(VK_LEFT)) {
		state->p1.movement = direction::left;
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		state->p1.movement = direction::right;
	}
	else if (GetAsyncKeyState(VK_DOWN)) {
		state->p1.movement = direction::none;
	}
	else if (GetAsyncKeyState(VK_ESCAPE)) { return true; }
	return false; // true if the user wants to quit the game
}

void game::update(game::game_state* state, std::chrono::steady_clock::duration delta) {

	double frameTime = delta.count() / 1e9;
	if ( frameTime > 0.1) {
		//return;
	}
											//skips update if frame took too long
	state->p1.update(frameTime);
	state->b1.update(frameTime, state->p1.rect, state->p1.getDirection());
	for (int i = 0; i < bricks_no; i++) {
		state->bricks[i].update(frameTime);
	}
}

void game::render(game::game_state state, std::chrono::time_point<std::chrono::steady_clock> c) {
	state.p1.render();
	state.b1.render();

	/*
	for (int i = 0; i < bricks_no; i++) {
		state.bricks[i].render();
	}
	*/
	//std::cout << "TEST" << std::endl;

	auto time_left = _timestep - (std::chrono::high_resolution_clock::now() - c);
	double t = time_left.count() / 1e6;
	if (t > 0) {
		Sleep(t);
	}
}

int game::loop() {
	using clock = std::chrono::high_resolution_clock;

	auto time_start = clock::now();
	bool quit_game = false;

	game::game_state current_state;

	borderSetup(current_state);

	while (!quit_game) {
		auto delta_time = clock::now() - time_start;
		time_start = clock::now();
		quit_game = game::handleEvents(&current_state);
		game::update(&current_state, delta_time);
		game::render(current_state, time_start);
	}
	return 0;
}



//init static member(s)