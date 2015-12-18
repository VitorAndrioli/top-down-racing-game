#ifndef CIRCLE_H
#define CIRCLE_H

#include "collidable.h"
#include "obb.h"
#include <iostream>

class Circle : public Collidable
{
protected:
	double m_dRadius;
public:
	Circle();
	Circle(double dPosX, double dPosY, double dRadius);
	double getRadius();
	void update(sf::Time elapsed);
};

#endif