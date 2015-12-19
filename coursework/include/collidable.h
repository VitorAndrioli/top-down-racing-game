#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <SFML/Graphics.hpp>
#include "vector2D.h"

class Collidable : public sf::Drawable
{
protected:
	Vector2D<double> m_dvPosition;
	Vector2D<double> m_dvVelocity;
	Vector2D<double> m_dvAcceleration;
	double m_dForce;
	double m_dAcceleration;
	double m_dVelocity;
	double m_dInverseMass;
	double m_dAngle;
	sf::VertexArray m_vaPoints;
public:
	Collidable();
	Vector2D<double> getPosition();
	Vector2D<double> getVelocity();
	Vector2D<double> getAcceleration();
	double getInverseMass();
	double getAngle();
	void accelerate();
	void decelerate();
	void turnRight();
	void turnLeft();
	void setPosition(Vector2D<double> position);
	void setVelocity(Vector2D<double> velocity);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
};

#endif