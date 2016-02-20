//! \file collidableFactory.cpp Implementation of CollidableFactory class.

#include "collidableFactory.h"

Collidable * CollidableFactory::generateCollidable(const rapidxml::xml_node<>* pNode)
{
	Collidable * collidable;
	collidable = makeCollidable(pNode);

	return collidable;
}

Collidable * CollidableFactory::makeCollidable(const rapidxml::xml_node<>* pNode)
{
	TextureManager *textureManager = TextureManager::getInstance();
	Collidable *collidable = nullptr;
	string sCollidableType = pNode->first_attribute("type")->value();

	if (sCollidableType == "obb")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());
		double fHalfExtentX = atof(pNode->first_attribute("halfExtentX")->value());
		double fHalfExtentY = atof(pNode->first_attribute("halfExtentY")->value());
		double fOrientation = atof(pNode->first_attribute("orientation")->value());

		collidable = new OBB(fPosX, fPosY, fHalfExtentX, fHalfExtentY, fOrientation * 3.14159 / 180);
	}
	if (sCollidableType == "circle")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());
		double fRadius = atof(pNode->first_attribute("radius")->value());

		collidable = new Circle(fPosX, fPosY, fRadius);
	}
	if (sCollidableType == "tyre")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());

		collidable = new Tyre(fPosX, fPosY);
	}
	if (sCollidableType == "box")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());
		double fSize = atof(pNode->first_attribute("size")->value());
		double fOrientation = atof(pNode->first_attribute("orientation")->value());

		collidable = new Box(fPosX, fPosY, fSize, fOrientation * 3.14159 / 180);
	}
	collidable->setTexture(textureManager->getImage(sCollidableType));
	return collidable;
}

