#pragma once
#define _WIN32_WINNT 0x0501 // windows.h version
#include <string>
#include <windows.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
class visibleObject
{
public:
	visibleObject();
	virtual ~visibleObject();
	virtual void render();
	virtual void update();
	virtual float getX() { return x; };
	virtual float getY() { return y; };

	std::string texture;
protected:
	float x, y;
	float prevX, prevY;
	float vx, vy;
	int color = 0;
	bool _isActive;
	bool _isStatic; // does this object move or not?

	friend class game;
};
