#pragma once

#include "config.h"
#include "ball.h"
#include "pad.h"
#include "brick.h"
#include "csvLib.h"

using namespace std::chrono_literals;
class game
{
	public:
		static constexpr std::chrono::nanoseconds _timestep{ 16ms }; // we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
		enum class main_state
		{
			uninitialized, showingSplash, showingMenu, playing, exiting, showingResult, newGame
		};
		enum class game_result {
			none, win, lose
		};
		struct game_state {
			ball b1;
			pad p1;
			std::vector<brick> bricks;

			main_state _mainState = main_state::showingSplash;
			game_result result = game_result::none;

			std::chrono::steady_clock::time_point scoreTimer;
			bool resuming = false;

			HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		};

		static bool handleEvents(game_state*);
		static void update(game_state*, std::chrono::steady_clock::duration);
		static void render(game_state, std::chrono::time_point<std::chrono::steady_clock>);
		static int loop();

		static void borderSetup(game_state);
		static void brickSetup(game_state&);
		static void showSplash(game_state&);
		static void showMenu(game_state&);
		static void showResult(game_state&);

		static void gotoxy(int x, int y)
		{
			COORD c = { x, y };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		}
		static long getScore(float timeInSeconds);
		static std::vector<std::pair<std::string, long>> parseScores(std::vector<std::vector<std::string> >);
		static void saveScores(std::vector<std::pair<std::string, long>>);
		static bool compareScores(const std::pair<std::string, long>, const std::pair<std::string, long>);
};
