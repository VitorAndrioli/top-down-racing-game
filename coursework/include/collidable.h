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
#include <iostream>

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
	double m_fOrientation;
	double m_fFrictionCoefficient;
	double m_fElasticity;
	double m_fRadius;
	
	Vector2D<double> m_fvAngularPosition;
	Vector2D<double> m_fvAngularVelocity;
	Vector2D<double> m_fvAngularAcceleration;
	Vector2D<double> m_fvTorque;
	double m_fAngularVelocity;
	double m_fTorque;
	double m_fInverseMomentOfInertia;
	
	sf::VertexArray m_vaPoints;
	
	bool broadCollisionCheck(Collidable * collidable);
	void resolveCollision(Collidable * collidable, Vector2D<double> * collisionNormal, double overlap);

public:
	sf::Sprite m_sprite;
	
	Collidable();
	void update(float elapsed);
	virtual void updatePoints() {};
	virtual void checkCollision(Collidable * collidable) = 0;
	virtual void checkCollision(Circle * circle) = 0;
	virtual void checkCollision(OBB * obb) = 0;
	bool isMoving();

	void print() { std::cout << getAcceleration().getX() << " | " << getAcceleration().getY() << std::endl; }
	
	Vector2D<double> getPosition();
	Vector2D<double> getVelocity();
	Vector2D<double> getAcceleration();
	Vector2D<double> getThrust();
	double getInverseMass();
	double getMass();
	double getOrientation();
	double getElasticity();
	double getFrictionCoefficient();
	double getRadius();
	void setPosition(Vector2D<double> fvPosition);
	void setVelocity(Vector2D<double> fvVelocity);
	void setAcceleration(Vector2D<double> fvAcceleration);
	void setThrust(Vector2D<double> fvThrust);
	void setOrientation(double fOrientation);
	void setMass(double fMass);
	void setFrictionCoefficient(double fFrictionCoefficient);
	void setElasticity(double fRestitution);
	void setRadius(double fRadius);

	void setTexture(sf::Texture texture);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif