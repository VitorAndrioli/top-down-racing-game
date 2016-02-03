/**
* \file collidable.h
*
* \class Collidable
*
*
* \brief Small text that appears on Classes page.
*
* Longer text that appears on
* description section
*
*
*/

#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <SFML/Graphics.hpp>
#include "vector2D.h"

class Circle;
class OBB;

class Collidable : public sf::Drawable
{
protected:
	Vector2D<double> m_fvPosition;
	Vector2D<double> m_fvVelocity;
	Vector2D<double> m_fvAcceleration;
	Vector2D<double> m_fvThrust;
	double m_fInverseMass;
	double m_fAngle;
	double m_fFrictionCoef;
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
	void setPosition(Vector2D<double> position);
	void setVelocity(Vector2D<double> velocity);
	void setAcceleration(Vector2D<double> acceleration);
	void setAngle(double angle);
	virtual void updatePoints() {};
	virtual void checkCollision(Collidable * collidable) = 0;
	virtual void checkCollision(Circle * circle) = 0;
	virtual void checkCollision(OBB * obb) = 0;
	void resolveImpulse(Collidable * collidable, Vector2D<double> * collisionNormal);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif