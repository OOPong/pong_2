#pragma once
#include "visibleObject.h"
#include "brick.h"
#include "pad.h"
class ball: public visibleObject
{
public:
	ball();
	void update(double, pad&, std::vector<brick>&);
	void render();
	void reset();

private:
	int size;

	double _velocity;
	double _angle;
	double _elapsedTimeSinceStart;

	double linearVelocityX(double angle);
	double linearVelocityY(double angle);

	float snap(float angle);

	bool isClamped(float, float, float);
	bool checkCollision1w(boundingRectangle, boundingRectangle);
	bool checkCollision2w(boundingRectangle, boundingRectangle);
	friend class game;
};
