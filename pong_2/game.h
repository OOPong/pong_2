#pragma once

#define _WIN32_WINNT 0x0501 // windows.h version
#define _CRT_SECURE_NO_WARNINGS

#include "ball.h"
#include "pad.h"
#include "brick.h"
#include <chrono>
#include <vector>
#include <list>
#include <Windows.h>
#include <iostream>
constexpr int width = 250;
constexpr int height = 250;
constexpr int bricks_no = 50;

using namespace std::chrono_literals;
class math {
public:
	enum class direction {
		right, left, bottom, top
	};
	static void move();
	static void intercept(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, direction d);
	static void ballIntercept();
};
class game
{
	public:
		static constexpr std::chrono::nanoseconds _timestep{ 16ms }; // we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
		enum class main_state
		{
			uninitialized, showingSplash, paused, showingMenu, playing, exiting, showingResult
		};
		struct game_state {
			ball b1;
			pad p1;
			brick bricks[bricks_no];
			main_state _mainState = main_state::uninitialized;
			HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		};
		static bool handleEvents();
		static void update(game_state*);
		static void render(game_state );
		static game_state interpolate(game_state const& current, game_state const& previous, float alpha);
		static int loop();

		static void gotoxy(int x, int y)
		{
			COORD c = { x, y };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		}
};
