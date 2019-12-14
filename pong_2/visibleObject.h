#pragma once
#include "config.h"

using namespace std::chrono_literals;
struct boundingRectangle {
	float x1, x2, y1, y2;
};
enum class direction {
	left, right, none
};
class visibleObject
{
public:
	visibleObject();
	virtual ~visibleObject();
	virtual void render();
	virtual void update(double);

	boundingRectangle rect;
	std::vector<std::string> texture;
	std::vector<std::string> clearTexture;

protected:
	float x, y;
	float prevX, prevY;
	float vx, vy;
	int color;
	bool _isActive; // does this object need to be updated and rendered?
	bool _isStatic; // does this object stay still?

	friend class game;
};
