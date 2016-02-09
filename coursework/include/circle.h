#ifndef CIRCLE_H
#define CIRCLE_H

#include "collidable.h"
#include "obb.h"
#include <iostream>

class Circle : public Collidable
{
public:
	Circle();
	Circle(double fPosX, double fPosY, double fRadius, double fAngle);
	void updatePoints();
	void checkCollision(Collidable * collidable);
	void checkCollision(Circle * circle);
	void checkCollision(OBB * obb);
};

#endif