#pragma once
#include "visibleObject.h"
#include "brick.h"
<<<<<<< HEAD
=======
#include "pad.h"
>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6
class ball: public visibleObject
{
public:
	ball();
<<<<<<< HEAD
	void update(double, boundingRectangle, direction, std::vector<brick>&);
	void render();
=======
	void update(double, pad&, std::vector<brick>&);
	void render();
	void reset();
>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6

private:
	int size;

	double _velocity;
	double _angle;
	double _elapsedTimeSinceStart;

	double linearVelocityX(double angle);
	double linearVelocityY(double angle);

<<<<<<< HEAD
	void collideWithBoundingRectangle(boundingRectangle r, double& distanceX, double& distanceY);
	bool isClamped(float, float, float);
	bool checkCollision1w(boundingRectangle, boundingRectangle);
	bool checkCollision2w(boundingRectangle, boundingRectangle);
=======
	float snap(float angle);

	bool isClamped(float, float, float);
	bool checkCollision1w(boundingRectangle, boundingRectangle);
	bool checkCollision2w(boundingRectangle, boundingRectangle);
	friend class game;
>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6
};
