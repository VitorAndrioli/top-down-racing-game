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
	m_bReverse = false;
}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::VertexArray tyre;
	tyre.resize(5);
	tyre.setPrimitiveType(sf::PrimitiveType::LinesStrip);

	Vector2D<double> pos = m_dvPosition;

	tyre[0].position.x = tyre[4].position.x = pos.getX() - 4;
	tyre[0].position.y = tyre[4].position.y = pos.getY() - 3;

	tyre[1].position.x = pos.getX() - 4;
	tyre[1].position.y = pos.getY() + 3;

	tyre[2].position.x = pos.getX() + 4;
	tyre[2].position.y = pos.getY() + 3;
	
	tyre[3].position.x = pos.getX() + 4;
	tyre[3].position.y = pos.getY() - 3;

	//Collidable::draw(target, states);
	target.draw(m_vaPoints, states);
	target.draw(tyre, states);
}

void Car::update(float elapsed)
{

	Collidable::update(elapsed);
	
	Vector2D<double> minVel(0.1, 0.1);

	Vector2D<double> maxVel(130, 0);
	maxVel.rotate(m_dAngle);

	if (abs(m_dvVelocity.squaredMagnitude()) > maxVel.squaredMagnitude())
	{
		m_dvVelocity = maxVel;
	}
	
	if (abs(m_dvVelocity.squaredMagnitude()) < minVel.squaredMagnitude())
	{
		m_dvVelocity = Vector2D<double>(0, 0);
	}


}

void Car::accelerate() {
	m_dvThrust = Vector2D<double>(100, 0);
	m_dvThrust.rotate(m_dAngle);
}

void Car::decelerate() {
	m_dvThrust = Vector2D<double>(0, 0);
}

void Car::reverse() {
	m_dvThrust = Vector2D<double>(-30, 0);
	m_dvThrust.rotate(m_dAngle);
}

void Car::turnRight()
{
	m_dAngle += (5 * M_PI / 180);
}

void Car::turnLeft()
{
	m_dAngle -= (5 * M_PI / 180);
}

