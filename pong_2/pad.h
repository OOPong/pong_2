#pragma once
#include "visibleObject.h"
class pad : public visibleObject
{
public:
	pad();
	void update(double);
	void render();
<<<<<<< HEAD
=======
	void reset();

>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6
	direction getDirection();

	direction movement = direction::none;
	long length;
	long height;
private:
	double _velocity;
<<<<<<< HEAD
=======
	friend class ball;
>>>>>>> c5bc662a6215cef27bff8ab6025ea503d84453d6
};

