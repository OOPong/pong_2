#pragma once
#include "visibleObject.h"
class brick: public visibleObject
{
public:
	brick(float x, float y, char no);

	void update(double);
	void render();
<<<<<<< HEAD
	void deactivate();

=======
	void blowUp();
	void deactivate();
	void reset();

	enum class powerUp {
		increasePadSize, decreasePadSize, increaseBallSpeed, decreaseBallSpeed
	};
>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6
	boundingRectangle getBoundingRect();

	long length;
	long height;
<<<<<<< HEAD
=======
	long breakTimer = -1;
	bool containPowerUp = false;
>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6
};

