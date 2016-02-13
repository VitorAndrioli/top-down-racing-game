#ifndef COLLIDABLE_FACTORY_H
#define COLLIDABLE_FACTORY_H

#include <collidable.h>
#include <obb.h>
#include <circle.h>
#include <SFML\Graphics.hpp>
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace std;

class CollidableFactory
{
public:
	static Collidable * NewCollidable(const rapidxml::xml_node<>* pNode);
	static Collidable * NewCollidable(const std::string &description);
	static string split(const std::string parameter, char delim);
};

#endif