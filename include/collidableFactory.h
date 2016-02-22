/*!
 * \file
 * \brief Declaration of CollidableFactory class.
 */

/*!
 * \class CollidableFactory collidableFactory.h "collidableFactory.h"
 * \brief Factory for creating different collidable objects.
 *
 * Implements Factory design pattern to assist in the generation of collidable objects
 * of different types (subclasses) from xml nodes.
 * 
 * \author Vitor Augusto Andrioli
 * \version 1.0
 * \date 25/02/2016
 */

#ifndef COLLIDABLE_FACTORY_H
#define COLLIDABLE_FACTORY_H

#include "collidable.h"
#include "obb.h"
#include "circle.h"
#include "tyre.h"
#include "box.h"
#include "textureManager.h"
#include <SFML\Graphics.hpp>
#include "rapidxml.hpp"
#include <memory>

using namespace std;

class CollidableFactory
{
public:
	CollidableFactory(); //!< Default constructor.
	Collidable* makeCollidable(const rapidxml::xml_node<>* pNode); //!< Makes a new collidable.
	~CollidableFactory(); //!< Default destructor.

protected:
	Collidable* generateCollidable(const rapidxml::xml_node<>* pNode); //!< Generates and assigns texture to a new collidable from xml node.
	TextureManager* m_pTextureManager; //!< Pointer to texture manager.
};

#endif