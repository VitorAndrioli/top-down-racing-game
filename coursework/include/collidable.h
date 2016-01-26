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
	Vector2D<double> m_dvThrust;
	double m_dInverseMass;
	double m_dAngle;
	float m_fFrictionCoef;
	sf::VertexArray m_vaPoints;
public:
	void print();
	Collidable();
	void update(float elapsed);
	Vector2D<double> getPosition();
	Vector2D<double> getVelocity();
	Vector2D<double> getAcceleration();
	double getInverseMass();
	double getAngle();
	/*void accelerate();
	void decelerate();
	void reverse();
	void turnRight();
	void turnLeft();*/
	void setPosition(Vector2D<double> position);
	void setVelocity(Vector2D<double> velocity);
	virtual void updatePoints() {};

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif