/*#pragma once

#include "car.h"
#include "circle.h"
#include "obb.h"

class Collision
{
public:
	Collision();
	void checkCollision(OBB * obb, Circle * circle);
	void checkCollision(Circle * circle, OBB * obb);
	bool checkCollision(OBB * obb1, OBB * obb2);
	void checkCollision(Circle * circle1, Circle * circle2);
	void checkCollision(Collidable * collidable1, Collidable * collidable2);
	void resolveImpulses(Collidable * collidable1, Collidable * collidable2, Vector2D<double> * collisionNormal);
};

*/