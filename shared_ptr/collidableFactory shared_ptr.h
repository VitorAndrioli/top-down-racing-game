//! \file collidableFactory.h Declaration of CollidableFactory class.

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
protected:
	shared_ptr<Collidable> generateCollidable(const rapidxml::xml_node<>* pNode);
public:
	shared_ptr<Collidable> makeCollidable(const rapidxml::xml_node<>* pNode);
};

#endif