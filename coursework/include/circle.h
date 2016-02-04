#ifndef CIRCLE_H
#define CIRCLE_H

#include "collidable.h"
#include "obb.h"
#include <iostream>

class Circle : public Collidable
{
protected:
	double m_fRadius;
public:
	Circle();
	Circle(double fPosX, double fPosY, double fRadius, double fAngle);
	void updatePoints();
	double getRadius();
	void setRadius(double fRadius);
	void checkCollision(Collidable * collidable);
	void checkCollision(Circle * circle);
	void checkCollision(OBB * obb);
};

#endif