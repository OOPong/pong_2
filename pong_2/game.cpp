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
	if (!(current_state.result == game_result::none)) {
		exit(0);
	}
	system("CLS");
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

	std::vector<std::string> items;
	items.push_back("NEW GAME");
	items.push_back("CONTINUE");
	items.push_back("SCORE");
	items.push_back("EXIT");
	int selectedIndex = 1;
	bool selected = false;

	for (int i = 0; i < items.size(); i++) {
		gotoxy(27, 17 + i);
		std::cout << items[i];
	}
	while (!selected) {
		gotoxy(20, 15);
		std::cout << "Your selection: " << items[selectedIndex - 1] << "          "<< std::endl;
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
	{
		current_state._mainState = main_state::newGame;
		break;
	}
	case 2:
	{
		if (current_state.resuming) {
			current_state._mainState = main_state::playing;
		}
		else {
			current_state._mainState = main_state::newGame;
		}
		break;
	}
	case 3:
		current_state._mainState = main_state::showingResult;
		break;
	case 4:
		current_state._mainState = main_state::exiting;
		break;
	default:
		break;
	}
}

void game::showResult(game::game_state& current_state)
{
	auto timeDifference = std::chrono::steady_clock::now() - current_state.scoreTimer;
	auto score = getScore(timeDifference.count());

	std::vector<std::vector<std::string> > lines;
	csvLib::parseCSV(csvLib::getFileContents("highscore.txt"), lines);
	std::vector<std::pair<std::string, long>> scores = parseScores(lines);

	system("CLS");

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
	gotoxy(23, 12);
	if (current_state.result == game_result::lose) {
		std::cout << "YOU LOSE!";
	}
	else if (current_state.result == game_result::win) {
		std::cout << "YOU WIN!";
		gotoxy(23, 13);
		std::cout << "YOUR SCORE: " << score << std::endl;
		gotoxy(15, 21);
		std::cout << "Press SPACE to save your score" << std::endl;
		gotoxy(0, 0);
	}
	gotoxy(23, 14);
	std::cout << "HIGH SCORES:" << std::endl;
	for (int i = 0; i < 5; i++) {
		gotoxy(25, 15+i);
		std::cout << "[" << i+1 << "]" << scores[i].first << ": " << scores[i].second << std::endl;
	}

	gotoxy(15, 20);
	std::cout << "Press ESCAPE to exit" << std::endl;

	bool selected = false;
	while (!GetAsyncKeyState(VK_ESCAPE)) {
		if (GetAsyncKeyState(VK_SPACE) && (current_state.result == game_result::win)) {
			gotoxy(20, 22);
			std::cout << "Please enter your name: ";
			gotoxy(20, 23);
			std::string tempname;
			std::cin >> tempname;
			scores.push_back(std::make_pair(tempname, score));
			saveScores(scores);
		}
	}
	current_state._mainState = main_state::exiting;
}

long game::getScore(float timeInSeconds)
{
	return 1e6;
	if (timeInSeconds > 180) {
		return 0;
	}
	else {
		return ((180 - timeInSeconds) * 100);
	}
}

std::vector<std::pair<std::string, long>> game::parseScores(std::vector<std::vector<std::string>> lines)
{
	std::vector<std::pair<std::string, long>> result;
	for (int i = 0; i < lines.size(); i++) {
		result.push_back(std::make_pair(lines[i][0], stol(lines[i][1])));
	}
	std::sort(result.begin(), result.end(), compareScores);
	return result;
}

void game::saveScores(std::vector<std::pair<std::string, long>> result)
{
	std::sort(result.begin(), result.end(), compareScores);
	std::vector<std::vector<std::string>> lines;
	for (int i = 0; i < result.size(); i++) {
		std::vector<std::string> temp;
		temp.push_back(result[i].first);
		temp.push_back(std::to_string(result[i].second));
		lines.push_back(temp);
	}
	csvLib::writeCSV("highscore.txt", lines);
}

bool game::compareScores(const std::pair<std::string, long> a, const std::pair<std::string, long> b)
{
	if (a.second < b.second) {
		return true;
	}
	return false;
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
	else if (GetAsyncKeyState(VK_ESCAPE)) {
		state->_mainState = main_state::showingMenu;
	}
	return false; // true if the user wants to quit the game
}

void game::update(game::game_state* state, std::chrono::steady_clock::duration delta) {

	double frameTime = delta.count() / 1e9;

	//skips update if frame took too long
	if (frameTime > 0.1) {
		return;
	}

	state->p1.update(frameTime);
	state->b1.update(frameTime, state->p1, state->bricks);

	for (int i = 0; i < state->bricks.size(); i++) {
		state->bricks[i].update(frameTime);
	}

	//if b1 out of bounds
	//lose
	if (state->b1.rect.y2 > (game_width / 10)) {
		state->result = game_result::lose;
		state->_mainState = main_state::showingResult;
	}
	for (int i = 0; i < state->bricks.size(); i++) {
		if (state->bricks[i]._isActive) {
			break;
		}
		state->result = game_result::win;
		state->_mainState = main_state::showingResult;
	}
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
		case main_state::newGame:
		{
			if (!current_state.resuming) {
				brickSetup(current_state);
				borderSetup(current_state);
				current_state.resuming = true;
				current_state.scoreTimer = std::chrono::steady_clock::now();
			}
			else {
				current_state.b1.reset();
				current_state.p1.reset();
			}
			current_state._mainState = main_state::playing;
			break;
		}
		case main_state::showingMenu:
		{
			showMenu(current_state);
			break;
		}
		case main_state::playing:
		{
			game::update(&current_state, delta_time);
			game::render(current_state, time_start);
			break;
		}
		case main_state::showingResult:
		{
			showResult(current_state);
			break;
		}
		case main_state::exiting:
		{
			quit_game = true;
			exit(0);
			break;
		}
		default:
			break;
		}

	}
	return 0;
}



//init static member(s)