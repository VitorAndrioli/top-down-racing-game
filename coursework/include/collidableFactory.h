//! \file collidableFactory.h Declaration of CollidableFactory class.

#ifndef COLLIDABLE_FACTORY_H
#define COLLIDABLE_FACTORY_H

#include <collidable.h>
#include <obb.h>
#include <circle.h>
#include <tyre.h>
#include "box.h"
#include "textureManager.h"
#include <SFML\Graphics.hpp>
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace std;

class CollidableFactory
{
public:
	static Collidable * NewCollidable(const rapidxml::xml_node<>* pNode, TextureManager * textureManager);
};

#endif