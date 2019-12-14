#pragma once
#include "visibleObject.h"
class brick: public visibleObject
{
public:
	brick(float x, float y, char no);

	void update(double);
	void render();
	void deactivate();

	boundingRectangle getBoundingRect();

	long length;
	long height;
};

