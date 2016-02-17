//! \file collidable.h Declaration of Collidable class.
/*!
 * \class Collidable
 *
 * \brief Base class for every collidable object in the game.
 *
 * Implements basic kinematics 
 *
 *
 */

#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#define TO_RADIANS  M_PI / 180 //!< Used to transform degrees to radians.
#define TO_DEGREES  180 / M_PI //!< Used transform radians to degrees.


#include <SFML/Graphics.hpp>
#include "vector2D.h"
#include <iostream>

//!< Forward declaration of child classes Circle and OBB to be used as parameters in virtual function checkCollision.
class Circle;
class OBB;

class Collidable : public sf::Drawable
{
protected:
	double m_fInverseMass;  //!< Inverse of collidable's mass.
	double m_fFrictionCoefficient; //!< Friction coefficient of collidable.
	double m_fRestitution; //!< Restitution coefficient.
	double m_fRadius; //!< Radius of collidable. Used for broad collision check for non circular child classes.

	// Linear components.
	Vector2D<double> m_fvPosition; //!< Center position vector.
	Vector2D<double> m_fvVelocity; //!< Velocity vector.
	Vector2D<double> m_fvAcceleration; //!< Acceleration vector.
	Vector2D<double> m_fvThrust; //!< Thrust vector.
	
	// Angular components
	double m_fOrientation; //!< Orientation of the collidable, in radians.
	//double m_fAngularVelocity; //!< Angular velocity.
	double m_fAngularAcceleration; //!< Angular vAcceleration.
	double m_fTorque; //!< Torque applied to object.
	double m_fInverseMomentOfInertia; //!< Inverse moment of inertia.
	
	sf::VertexArray m_vaPoints; //!< Points to be drawn (to be removed)
	sf::Sprite m_sprite; //!< Sprite to be drawn to the window.

	bool broadCollisionCheck(Collidable * otherCollidable); //!< Perform a broad and less costly collision check with another collidable.
	void resolveCollision(Collidable * otherCollidable, Vector2D<double> * fvCollisionNormal, double fOverlap); //!< Resolve collision between two colliding objects. 
	void resolveCollision(Collidable * otherCollidable, Vector2D<double> * fvCollisionNormal, double fOverlap, Vector2D<double> * fvContactPoint); //!< Resolve collision between two colliding objects. 
	void applyImpulse(Vector2D<double> * fvImpulse, Vector2D<double> * fvContactPoint); //!< Apply an impulse (sudden change of velocity) to the object.

public:
	double m_fAngularVelocity; //!< protected
	
	
	Collidable(); //!< Basic contructor.
	void update(float elapsed); //!< Update method. To be called every frame of the game.
	virtual void updatePoints() {}; //!< to be removed.
	void updateSprite(); //!< Updates the sprite position and orientation.
	bool isMoving(); //!< Check if the collidable is moving.
	
	// Virtual methods.
	virtual void checkCollision(Collidable * collidable) = 0; //!< Virtual method to check collision with another Collidable object.
	virtual void checkCollision(Circle * circle) = 0; //!< Virtual method to check collision with a Circle object.
	virtual void checkCollision(OBB * obb) = 0; //!< Virtual method to check collision with an OBB object.
	virtual void setTexture(sf::Texture * texture) = 0; //!< Virtual method to assign a texture to the object's sprite.

	// Setter and getters
	void setPosition(Vector2D<double> fvPosition);
	void setVelocity(Vector2D<double> fvVelocity);
	void setAcceleration(Vector2D<double> fvAcceleration);
	void setThrust(Vector2D<double> fvThrust);
	void setOrientation(double fOrientation);
	void setMass(double fMass);
	void setFrictionCoefficient(double fFrictionCoefficient);
	void setRestitution(double fRestitution);
	void setRadius(double fRadius);
	Vector2D<double> getPosition();
	Vector2D<double> getVelocity();
	Vector2D<double> getAcceleration();
	Vector2D<double> getThrust();
	double getOrientation();
	double getMass();
	double getInverseMass();
	double getFrictionCoefficient();
	double getRestitution();
	double getRadius();
	double getInverseInertia();
	


	void print() { std::cout << "Car: " << getVelocity().magnitude() << " | " << getAcceleration().getY() << std::endl; } //!< to be removed.


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //!< Virtual draw method from Drawable class.
};

#endif