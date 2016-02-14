/*!
* \file collidable.h
* \class Collidable
*
*
* \brief Base class for every collidable object in the game.
*
* Longer text that appears on
* description section
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
	Vector2D<double> m_fvPosition; //!< Center position vector.
	Vector2D<double> m_fvVelocity; //!< Velocity vector.
	Vector2D<double> m_fvAcceleration; //!< Acceleration vector.
	Vector2D<double> m_fvThrust; //!< Thrust vector.
	double m_fInverseMass;  //!< Inverse of collidable's mass.
	double m_fOrientation; //!< Orientation of the collidable, in radians.
	double m_fFrictionCoefficient; //!< Friction coefficient of collidable.
	double m_fRestitution; //!< Restitution coefficient.
	double m_fRadius; //!< Radius of collidable. Used for broad collision check for non circular child classes.
	
	Vector2D<double> m_fvAngularPosition; //!< 
	Vector2D<double> m_fvAngularVelocity; //!< 
	Vector2D<double> m_fvAngularAcceleration; //!< 
	Vector2D<double> m_fvTorque; //!< 
	double m_fAngularVelocity; //!< 
	double m_fTorque; //!< 
	double m_fInverseMomentOfInertia; //!< 
	
	sf::VertexArray m_vaPoints; //!< Points to be drawn (to be removed)
	sf::Sprite m_sprite; //!< Sprite to be drawn to the window

	/*!
	*	\brief Perform a broad collision check with another collidable.
	*
	*	Use both collidable's radii to perform quicker collision detection testes before advancing to more costly methods.
	*/
	bool broadCollisionCheck(Collidable * otherCollidable);

	/*!
	*	\brief Resolve collision between two collidable objects. 
	*
	*	Resolve overlap of two colliding objects, calculate and update their velocities.
	*/
	void resolveCollision(Collidable * otherCollidable, Vector2D<double> * fvCollisionNormal, double fOverlap); 

public:
	Collidable(); //!< Basic contructor
	void update(float elapsed); //!< Update method to be called every frame of the game.
	virtual void updatePoints() {}; //!< to be removed.
	void updateSprite(); //!< Updates the sprite.

	virtual void checkCollision(Collidable * collidable) = 0; //!< Virtual method to check collision with another Collidable object.
	virtual void checkCollision(Circle * circle) = 0; //!< Virtual method to check collision with a Circle object.
	virtual void checkCollision(OBB * obb) = 0; //!< Virtual method to check collision with an OBB object.
	bool isMoving(); //!< Check if the collidable is moving. Called befor performing collision tests. \return bool

	void print() { std::cout << getVelocity().magnitude() << " | " << getAcceleration().getY() << std::endl; } //!< to be removed.
	
	//!< Get methods

	Vector2D<double> getPosition();
	Vector2D<double> getVelocity();
	Vector2D<double> getAcceleration();
	Vector2D<double> getThrust();
	double getInverseMass();
	double getMass();
	double getOrientation();
	double getRestitution();
	double getFrictionCoefficient();
	double getRadius();
	
	//!< Set methods
	
	void setPosition(Vector2D<double> fvPosition);
	void setVelocity(Vector2D<double> fvVelocity);
	void setAcceleration(Vector2D<double> fvAcceleration);
	void setThrust(Vector2D<double> fvThrust);
	void setOrientation(double fOrientation);
	void setMass(double fMass);
	void setFrictionCoefficient(double fFrictionCoefficient);
	void setRestitution(double fRestitution);
	void setRadius(double fRadius);
	virtual void setTexture(sf::Texture * texture) = 0;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif