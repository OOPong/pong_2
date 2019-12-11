#include "ball.h"

ball::ball()
{
	size = 1;

	x = 5;
	y = 8;

	prevX = x;
	prevY = y;

	_velocity = 3;
	_angle = 60.0f;

	_isActive = true;
	_isStatic = true; // toggle to on when countdown ends

	for (int i = 0; i < size; i++) {
		texture.push_back(std::string(size,'0'));
		clearTexture.push_back(std::string(size, ' '));
	}
}

void ball::update(double delta, boundingRectangle pad, direction padDirection, std::vector<brick>& bricks)
{
	//delta = 0.1;

	prevX = x;
	prevY = y;

	double distanceX = linearVelocityX(_angle) * _velocity * delta;
	double distanceY = linearVelocityY(_angle) * _velocity * delta;

	//bounce from side walls
	if ( ((x + distanceX) < 0.2) || ((x + (double(size) / 10) + distanceX) > ((game_width / 10) - 0.3))) {
		_angle = 360.0f - _angle;

		if (_angle > 260.0f && _angle < 280.0f) {
			_angle += 20.f;
		}

		if (_angle > 80.0f && _angle < 100.0f) {
			_angle += 20.f;
		}

		distanceX = distanceX * -1;
	}

	//bounce from top + bottom walls
	//disable bottom walls on release
	if (((y + distanceY) < 0.2) || ((y + (double(size) / 10) + distanceY) > ((game_height / 10) - 0.2))) {
		_angle = 180.0f - _angle;


		if (_angle > 260.0f && _angle < 280.0f) {
			_angle += 20.f;
		}

		if (_angle > 80.0f && _angle < 100.0f) {
			_angle += 20.f;
		}

		distanceY = distanceY * -1;
	}

	if (_angle > 360.0f) {
		_angle = float(int(_angle) % int(360.0f));
	}

	//bounce with player paddle
	if (checkCollision2w(rect, pad)) {

		//ball approaching from top side
		if ((rect.y2 > pad.y1) && (90 <= _angle && _angle <= 270)) {
			y -= (rect.y2 - pad.y1) + 0.1f;
		}
		// y2: bottom ball border
		// difference is how deep the ball is inside
		// get it out by subtracting by this amount

		//ball approaching from bottom side
		if ((rect.y1 < pad.y2) && ((0 <= _angle && _angle <= 90) || (270 <= _angle && _angle <= 360))) {
			y += (pad.y2 - rect.y1) + 0.1f;
		}
		// y1: top ball border
		// difference is how deep the ball is inside
		// get it out by adding this amount

		//ball approaching from left side
		if ((rect.x2 > pad.x1) && (0 < _angle && _angle < 180)) {
			x -= (rect.x2 - pad.x1) + 0.1f;
		}

		//ball approaching from right side
		if ((rect.x1 < pad.x2) && (180 < _angle && _angle < 360)) {
			x += (pad.x2 - rect.x1) + 0.1f;
		}
		_angle = 360.0f - (_angle - 180.0f);

		if (1){//_angle > 5.0f && _angle < 355.0f) {
			if (padDirection == direction::left)
			{
				// moving left
				_angle -= 15.0f;
				if (_angle < 0) {
					_angle = 360.0f - _angle;
				}
			}
			else if (padDirection == direction::right)
			{
				_angle += 15.0f;
				if (_angle > 360.0f) {
					_angle = _angle - 360.0f;
				}
			}
		}


		distanceX = linearVelocityX(_angle) * _velocity * delta;
		distanceY = linearVelocityY(_angle) * _velocity * delta;

		_velocity = _velocity * 1.1f;
	}

	//bounce and break bricks
	bool collided = false;
	for (int i = 0; i < bricks.size(); i++) {
		if (bricks[i]._isActive && (checkCollision2w(rect, bricks[i].getBoundingRect())) && !collided) {

			auto a = bricks[i].getBoundingRect();

			//ball approaching from top side
			if ((rect.y2 > a.y1) && (90 <= _angle && _angle <= 270)) {
				y -= (rect.y2 - a.y1);
			}
			// y2: bottom ball border
			// difference is how deep the ball is inside
			// get it out by subtracting by this amount

			//ball approaching from bottom side
			if ((rect.y1 < a.y2) && ((0 <= _angle && _angle <= 90) || (270 <= _angle && _angle <= 360))) {
				y += (a.y2 - rect.y1);
			}
			// y1: top ball border
			// difference is how deep the ball is inside
			// get it out by adding this amount

			//ball approaching from left side
			if ((rect.x2 > a.x1) && (0 < _angle && _angle < 180)) {
				x -= (rect.x2 - a.x1);
			}

			//ball approaching from right side
			if ((rect.x1 < a.x2) && (180 < _angle && _angle < 360)) {
				x += (a.x2 - rect.x1);
			}

			_angle = 360.0f - (_angle - 180.0f);

			distanceX = linearVelocityX(_angle) * _velocity * delta;
			distanceY = linearVelocityY(_angle) * _velocity * delta;
			bricks[i].deactivate();
			collided = true;
		}
	}

	x += distanceX;
	y += distanceY;

	if (_velocity > 5) {
		_velocity = 5;
	}


	//snap to nearest 15 deg angle
	_angle = snap(_angle);


	//update bounding rectangle
	rect.x1 = x - double(size) / 10;
	rect.x2 = x + double(size) / 10;
	rect.y1 = y - double(size) / 10;
	rect.y2 = y + double(size) / 10;
}

void ball::render()
{
	int margin = size - 1;
	for (int i = 0; i < texture.size(); i++) {
		COORD c = { round(prevX * 10) - margin, round(prevY * 10) - margin + i }; //-1 because ball coords is centered
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		std::cout << std::flush << clearTexture[i];
	}
	for (int i = 0; i < texture.size(); i++) {
		COORD c = { round(x * 10) - margin, round(y * 10) - margin + i }; // -1 because ball coords is centered
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		std::cout << std::flush << texture[i];
	}
}

bool ball::isClamped(float mid, float A, float B)
{
	if (A > B)
	{
		return mid >= B && mid <= A;
	}
	return mid >= A && mid <= B;
}

bool ball::checkCollision1w(boundingRectangle rectA, boundingRectangle rectB)
{
	if ((isClamped(rectA.x1, rectB.x1, rectB.x2)
		|| isClamped(rectA.x2, rectB.x1, rectB.x2))
		&& (isClamped(rectA.y2, rectB.y2, rectB.y1)
			|| isClamped(rectA.y1, rectB.y2, rectB.y1)))
	{
		return true;
	}
	return false;
}

bool ball::checkCollision2w(boundingRectangle rectA, boundingRectangle rectB)
{
	return checkCollision1w(rectA, rectB) || checkCollision1w(rectB, rectA);
}
double ball::linearVelocityX(double angle)
{
	angle -= 90;
	if (angle < 0) {
		angle = 360 + angle;
	}
	return (float)std::cos(angle * (M_PI / 180.0f));
}
double ball::linearVelocityY(double angle)
{
	angle -= 90;
	if (angle < 0) {
		angle = 360 + angle;
	}
	return (float)std::sin(angle * (M_PI / 180.0f));
}
float ball::snap(float angle)
{
	int remainder = abs(int(angle)) % 15;
	if (remainder == 0)
		return angle;

	if (angle < 0)
		return -(abs(int(angle)) - remainder);
	else
		return angle + 15 - remainder;
}
void ball::collideWithBoundingRectangle(boundingRectangle r, double& distanceX, double& distanceY)
{
	//x1<x2
	//y1<y2
	if (checkCollision2w(rect, r)) {

	}

}