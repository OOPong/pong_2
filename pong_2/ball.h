﻿#pragma once
#include "visibleObject.h"
class ball: public visibleObject
{
public:
	ball();
	void update(double, boundingRectangle, direction);
	void render();

private:
	int size;

	double _velocity;
	double _angle;
	double _elapsedTimeSinceStart;

	double linearVelocityX(double angle);
	double linearVelocityY(double angle);

	void collideWithBoundingRectangle(boundingRectangle r, double& distanceX, double& distanceY);
	bool isClamped(float, float, float);
	bool checkCollision1w(boundingRectangle, boundingRectangle);
	bool checkCollision2w(boundingRectangle, boundingRectangle);
};