#pragma once

#include "car.h"
#include "circle.h"
#include "obb.h"

class Collision
{
public:
	Collision();
	bool checkCollision(OBB * obb, Circle * circle);
	bool checkCollision(Circle * circle, OBB * obb);
	bool checkCollision(OBB * obb1, OBB * obb2);
	bool checkCollision(Circle * circle1, Circle * circle2);
};

