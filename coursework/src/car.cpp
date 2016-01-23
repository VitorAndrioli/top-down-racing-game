#include <SFML\Graphics.hpp>
#include "car.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace sf;

Car::Car()
{

}

Car::Car(double dPosX, double dPosY, double dAngle) : OBB(dPosX, dPosY, 30, 19, dAngle)
{
}

void Car::update(float elapsed)
{
	
	OBB::update(elapsed);

}
