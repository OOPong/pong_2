#pragma once

//constants
constexpr int game_width = 100;
constexpr int game_height = 100;
constexpr int bricks_grid_height = 7;
constexpr int bricks_grid_width = 9;
constexpr static int colors[6] = { 31, 47, 79, 63, 95, 111 };

//directives
#define _WIN32_WINNT 0x0501 // windows.h version
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

//libraries
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <ctime>
#include <algorithm>

#include <stdlib.h>
#include <cstdlib>
#include <cmath>

#include <Windows.h>
