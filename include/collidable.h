/*!
* \file
* \brief Declaration of Collidable class.
*/

/*!
 * \class Collidable collidable.h "collidable.h"
 * \brief Template class for every collidable object in the game.
 *
 * Implements basic mechanics and integration methods to move objects, 
 * as well as broad collision tests, collision response and impulse application.
 * Declares virtual methods for detecting collision, allowing polymorphic calls.
 *
 * \author Vitor Augusto Andrioli
 * \version 1.0
 * \date 25/02/2016
 *
 * \todo Add angular movement.
 */

#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML/Graphics.hpp>
#include "vector2D.h"
#include <memory>
#include <iostream>

#define TO_RADIANS  M_PI / 180 //!< Used to transform degrees to radians.
#define TO_DEGREES  180 / M_PI //!< Used to transform radians to degrees.
#define STOPPING_VELOCITY  10 //!< (Squared) Used to stop moving collidables.

using namespace std;

// Forward declaration of child classes Circle and OBB to be used as parameters in virtual function checkCollision.
class Circle;
class OBB;

class Collidable : public sf::Drawable
{
public:
	Collidable(); //!< Default contructor.
	void update(float fElapsed); //!< Update method to be called every frame of the game.
	void updateSprite(); //!< Updates the sprite position and orientation.
	bool moved(); //!< Checks if the collidable has moved linearly or rotated since last frame.
	bool isMoving(); //!< Checks if the collidable is moving linearly.
	bool isRotating(); //!< Checks if the collidable is rotating.
	
	// Virtual methods.
	virtual void checkCollision(Collidable* const pCollidable) = 0; //!< Virtual method to check collision with another Collidable object.
	virtual void checkCollision(Circle* const pCircle) = 0; //!< Virtual method to check collision with a Circle object.
	virtual void checkCollision(OBB* const pObb) = 0; //!< Virtual method to check collision with an OBB object.
	virtual void setTexture(shared_ptr<sf::Texture> pTexture) = 0; //!< Virtual method to assign a texture to the object's sprite.

	// Setter and getters
	void setPosition(Vector2D<double> fvPosition);
	void setPosition(double fPositionX, double fPositionY);
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
	
protected:
	double m_fInverseMass;  //!< Inverse of collidable's mass.
	double m_fFrictionCoefficient; //!< Friction coefficient of collidable.
	double m_fRestitution; //!< Restitution coefficient.
	double m_fRadius; //!< Radius of collidable. For non circular child classes it is used in broad collision checks.

	// Linear components.
	Vector2D<double> m_fvPosition; //!< Center position vector.
	Vector2D<double> m_fvVelocity; //!< Velocity vector.
	Vector2D<double> m_fvAcceleration; //!< Acceleration vector.
	Vector2D<double> m_fvThrust; //!< Thrust vector.

	// Angular components
	double m_fOrientation; //!< Orientation of the collidable, in radians.
	double m_fAngularVelocity; //!< Angular velocity.
	double m_fAngularAcceleration; //!< Angular acceleration.
	double m_fTorque; //!< Torque applied to object.
	double m_fInverseMomentOfInertia; //!< Inverse moment of inertia.

	sf::Sprite m_sprite; //!< Sprite to be drawn to the window.

	//! Performs a broad and less costly collision check with another collidable.
	bool broadCollisionCheck(Collidable* const pOtherCollidable);
	//! Resolves collision between two colliding objects. 
	void resolveCollision(Collidable* pOtherCollidable, Vector2D<double>* pfvCollisionNormal, double fOverlap, Vector2D<double>* pfvContactPoint);
	//! Applies an impulse (sudden change of velocity) to the object.
	void applyImpulse(Vector2D<double>* pfvImpulse, Vector2D<double>* pfvContactPoint);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const; //!< Virtual draw method inherited from Drawable class.
};

#endif