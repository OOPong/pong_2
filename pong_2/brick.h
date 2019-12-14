#pragma once
#include "visibleObject.h"
class brick: public visibleObject
{
public:
	brick(float x, float y, char no);
	void update(double);
	void render();

	long length;
	long height;
};

