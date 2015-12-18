#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <SFML/Graphics.hpp>
#include "vector.h"

class Collidable : public sf::Drawable
{
protected:
	Vector<double> m_dvPosition;
	Vector<double> m_dvVelocity;
	Vector<double> m_dvAcceleration;
	double m_dForce;
	double m_dAcceleration;
	double m_dVelocity;
	double m_dInverseMass;
	double m_dAngle;
	sf::VertexArray m_vaPoints;

public:
	Collidable();
	Vector<double> getPosition();
	Vector<double> getVelocity();
	Vector<double> getAcceleration();
	double getInverseMass();
	double getAngle();
	void setPosition(Vector<double> newPosition);
	void accelerate();
	void decelerate();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
};

#endif