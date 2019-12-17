#pragma once

#include "config.h"
#include "ball.h"
#include "pad.h"
#include "brick.h"
<<<<<<< HEAD
=======
#include "csvLib.h"

>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6
using namespace std::chrono_literals;
class game
{
	public:
		static constexpr std::chrono::nanoseconds _timestep{ 16ms }; // we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
		enum class main_state
		{
<<<<<<< HEAD
			uninitialized, showingSplash, paused, showingMenu, playing, exiting, showingResult
=======
			uninitialized, showingSplash, showingMenu, playing, exiting, showingResult, newGame
		};
		enum class game_result {
			none, win, lose
>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6
		};
		struct game_state {
			ball b1;
			pad p1;
			std::vector<brick> bricks;
<<<<<<< HEAD
			main_state _mainState = main_state::uninitialized;
			HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		};
=======

			main_state _mainState = main_state::showingSplash;
			game_result result = game_result::none;

			std::chrono::steady_clock::time_point scoreTimer;
			bool resuming = false;

			HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		};

>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6
		static bool handleEvents(game_state*);
		static void update(game_state*, std::chrono::steady_clock::duration);
		static void render(game_state, std::chrono::time_point<std::chrono::steady_clock>);
		static int loop();
<<<<<<< HEAD
		static void borderSetup(game_state);
=======

		static void borderSetup(game_state);
		static void brickSetup(game_state&);
		static void showSplash(game_state&);
		static void showMenu(game_state&);
		static void showResult(game_state&);
>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6

		static void gotoxy(int x, int y)
		{
			COORD c = { x, y };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		}
<<<<<<< HEAD
=======
		static long getScore(float timeInSeconds);
		static std::vector<std::pair<std::string, long>> parseScores(std::vector<std::vector<std::string> >);
		static void saveScores(std::vector<std::pair<std::string, long>>);
		static bool compareScores(const std::pair<std::string, long>, const std::pair<std::string, long>);
>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6
};
