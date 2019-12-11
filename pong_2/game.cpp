#include "game.h"
using namespace std::chrono_literals;

void game::borderSetup(game::game_state current_state)
{
	system("CLS");

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

	//hide cursor
	CONSOLE_CURSOR_INFO ConCurInf;
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = false;
	SetConsoleCursorInfo(current_state.stdHandle, &ConCurInf);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	//print frame
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

void game::brickSetup(game_state& current_state)
{
	//add bricks
	float vleftovers = 1; // starts placing bricks at y=1
	//int count = 0;
	for (int i = 0; i < bricks_grid_height; i++) {
		float totalBricksWidth = bricks_grid_width * 1; // brick width = 1;;
		float hleftovers = (game_width / 10) - totalBricksWidth;
		float leftside = hleftovers / 2;
		for (int j = 0; j < bricks_grid_width; j++) {
			brick tempBrick(leftside - 0.5 + (double(j) + 1) * 1, vleftovers + (double(i) + 1) * 0.4, '.');
			current_state.bricks.push_back(tempBrick);
			//count++;
		}
	}
}

void game::showSplash(game::game_state& current_state)
{
	//change font size
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = int(game_width / 10);                   // Width of each character in the font
	cfi.dwFontSize.Y = int(game_height / 5);                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(current_state.stdHandle, FALSE, &cfi);

	//set console
	HWND hwnd = GetConsoleWindow();
	RECT rect = { 100, 300, 820, 967 };
	MoveWindow(hwnd, rect.top, rect.left, rect.bottom - rect.top, rect.right - rect.left, TRUE);

	//hide cursor
	CONSOLE_CURSOR_INFO ConCurInf;
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = false;
	SetConsoleCursorInfo(current_state.stdHandle, &ConCurInf);

	gotoxy(27, 13);
	std::cout << "PONG GAME" << std::endl;
	gotoxy(30, 15);
	std::cout << "V2" << std::endl;
	for (int j = 16; j < 255; j++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), j);
		//print frame
		gotoxy(0, 0);
		for (int i = 0; i < 60; i++) {
			std::cout << ' ';
		}
		for (int i = 0; i < 32; ++i) {
			gotoxy(0, i);
			std::cout << ' ';
			gotoxy(60, i);
			std::cout << ' ';
		}
		for (int i = 0; i < 60+1; i++) {
			std::cout << ' ';
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(20, 20);
	std::cout << "Press SPACE to continue" << std::endl;
	gotoxy(0, 0);
	while (!GetAsyncKeyState(VK_SPACE));
	current_state._mainState = main_state::showingMenu;
}

void game::showMenu(game::game_state& current_state)
{
	system("CLS");
	std::vector<std::string> items;
	items.push_back("PLAY");
	items.push_back("EXIT");
	int selectedIndex = 1;
	bool selected = false;

	for (int i = 0; i < items.size(); i++) {
		gotoxy(27, 17 + i);
		std::cout << items[i];
	}
	while (!selected) {
		gotoxy(20, 15);
		std::cout << "Your selection: " << items[selectedIndex - 1] << std::endl;
		if (GetAsyncKeyState(VK_UP)) {
			if (selectedIndex - 1 < 1) {
				selectedIndex = items.size();
			}
			else {
				selectedIndex -= 1;
			}
			Sleep(200);
			continue;
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			if (selectedIndex + 1 > items.size()) {
				selectedIndex = 1;
			}
			else {
				selectedIndex += 1;
			}
			Sleep(200);
			continue;
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			selected = true;
		}
	}
	switch (selectedIndex)
	{
	case 1:
		current_state._mainState = main_state::playing;
		break;
	case 2:
		current_state._mainState = main_state::exiting;
		exit(0);
		break;
	default:
		break;
	}
}

void game::showResult(game::game_state current_state)
{
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

	//skips update if frame took too long
	if (frameTime > 0.1) {
		return;
	}

	state->p1.update(frameTime);
	state->b1.update(frameTime, state->p1.rect, state->p1.getDirection(), state->bricks);

	for (int i = 0; i < state->bricks.size(); i++) {
		state->bricks[i].update(frameTime);
	}

	//if b1 out of bounds
	//deduct points
	//if points = 0
	//set game state to showing results
}

void game::render(game::game_state state, std::chrono::time_point<std::chrono::steady_clock> c) {
	state.p1.render();
	state.b1.render();

	for (int i = 0; i < bricks_grid_height * bricks_grid_width; i++) {
		state.bricks[i].render();
	}

	//sleep remaining time
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

	while (!quit_game) {
		auto delta_time = clock::now() - time_start;
		time_start = clock::now();
		quit_game = game::handleEvents(&current_state);
		switch (current_state._mainState)
		{
		case main_state::uninitialized:
			break;
		case main_state::showingSplash:
		{
			showSplash(current_state);
			break;
		}
		case main_state::paused:
			break;
		case main_state::showingMenu:
		{
			showMenu(current_state);
			brickSetup(current_state);
			borderSetup(current_state);
			break;
		}
		case main_state::playing:
		{
			game::update(&current_state, delta_time);
			game::render(current_state, time_start);
		}
		case main_state::showingResult:
		{
			showResult(current_state);
			break;
		}
		case main_state::exiting:
			break;
		default:
			break;
		}

	}
	return 0;
}



//init static member(s)