#pragma once
#include "visibleObject.h"
class brick: public visibleObject
{
public:
	brick(float x, float y, char no);

	void update(double);
	void render();
	void blowUp();
	void deactivate();
	void reset();

	enum class powerUp {
		increasePadSize, decreasePadSize, increaseBallSpeed, decreaseBallSpeed
	};
	boundingRectangle getBoundingRect();

	long length;
	long height;
	long breakTimer = -1;
	bool containPowerUp = false;
};

