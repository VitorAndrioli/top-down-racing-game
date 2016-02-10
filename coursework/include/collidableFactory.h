#pragma once

#include <collidable.h>
#include <obb.h>
#include <circle.h>

class CollidableFactory
{
public:
	static Collidable * NewCollidable(const std::string &description)
	{
		if (description == "obb")
			return new OBB(450, 300, 20, 200, 0 * 3.14159 / 180);
		if (description == "circle")
			return new Circle(300, 300, 25, 0);
		return NULL;
	}
};

