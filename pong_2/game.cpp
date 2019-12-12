#define _CRT_SECURE_NO_WARNINGS
/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Mario Badr
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "game.h"
using namespace std::chrono_literals;


bool game::handleEvents() {
	// poll for events

	return false; // true if the user wants to quit the game
}

void game::update(game::game_state* state) {
	// update game logic here
	state->p1.update();
	state->b1.update();
	for (int i = 0; i < bricks_no; i++) {
		state->bricks[i].update();
	}
}

void game::render(game::game_state state) {
	// render stuff here
	state.p1.render();
	state.b1.render();
	/*
	for (int i = 0; i < bricks_no; i++) {
		state.bricks[i].render();
	}
	*/
	//std::cout << "TEST" << std::endl;
}


game::game_state game::interpolate(game::game_state const& current, game::game_state const& previous, float alpha) {
	//game::game_state interpolated_state;

	// interpolate between previous and current by alpha here

	return current;
}

int game::loop() {
	using clock = std::chrono::high_resolution_clock;

	std::chrono::nanoseconds lag(0ns);
	auto time_start = clock::now();
	bool quit_game = false;

	game::game_state current_state;
	game::game_state previous_state;


	//change font size
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 2;                   // Width of each character in the font
	cfi.dwFontSize.Y = 2;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(current_state.stdHandle, FALSE, &cfi);

	//set console
	HWND hwnd = GetConsoleWindow();
	RECT rect = { 100, 100, 750, 750 };
	MoveWindow(hwnd, rect.top, rect.left, rect.bottom - rect.top, rect.right - rect.left, TRUE);


	//hide cursor
	CONSOLE_CURSOR_INFO ConCurInf;
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = false;
	SetConsoleCursorInfo(current_state.stdHandle, &ConCurInf);

	//in ra khung bàn chơi
	SetConsoleTextAttribute(current_state.stdHandle, 15);
	for (int i = 0; i < width - 1; ++i)
		std::cout << '-';
	std::cout << std::endl;
	for (int i = 0; i < height - 1; ++i) {
		std::cout << "|";
		gotoxy(width-2,i);
		std::cout << "|" << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < width - 1; ++i)
		std::cout << '=';

	while (!quit_game) {
		auto delta_time = clock::now() - time_start;
		time_start = clock::now();
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

		quit_game = game::handleEvents();

		// update game logic as lag permits
		while (lag >= game::_timestep) {
			lag -= game::_timestep;

			previous_state = current_state;
			game::update(&current_state); // update at a fixed rate each time
		}

		// calculate how close or far we are from the next timestep
		auto alpha = (float)lag.count() / game::_timestep.count();
		auto interpolated_state = interpolate(current_state, previous_state, alpha);

		game::render(interpolated_state);
	}
	return 0;
}

//init static member(s)