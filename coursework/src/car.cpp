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
