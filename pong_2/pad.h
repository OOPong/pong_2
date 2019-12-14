#pragma once
#include "visibleObject.h"
class pad : public visibleObject
{
public:
	pad();
	void update(double);
	void render();
	direction getDirection();

	direction movement = direction::none;
	long length;
	long height;
private:
	double _velocity;
};

