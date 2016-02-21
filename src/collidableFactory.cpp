/*!
 * \file
 * \brief Implementation of CollidableFactory class.
 */

#include "collidableFactory.h"

// Gets the instance of Singleton Texture manager.
CollidableFactory::CollidableFactory() :
	m_pTextureManager(TextureManager::getInstance())
{ 
}

/*
 * \param pNode Pointer to a xml node.
 *
 * \return Pointer to a Collidable instance.
 */
Collidable* CollidableFactory::generateCollidable(const rapidxml::xml_node<>* pNode)
{
	Collidable* pCollidable;
	pCollidable = makeCollidable(pNode);

	return pCollidable;
}

/*
* \param pNode Pointer to a xml node.
*
* \return Pointer to a Collidable instance.
*/
Collidable* CollidableFactory::makeCollidable(const rapidxml::xml_node<>* pNode)
{
	// Gets type of the collidable to be created.
	string sCollidableType = pNode->first_attribute("type")->value();
	Collidable* pCollidable = nullptr;

	// Creates an object of the type received.
	if (sCollidableType == "obb")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());
		double fHalfExtentX = atof(pNode->first_attribute("halfExtentX")->value());
		double fHalfExtentY = atof(pNode->first_attribute("halfExtentY")->value());
		double fOrientation = atof(pNode->first_attribute("orientation")->value());

		pCollidable = new OBB(fPosX, fPosY, fHalfExtentX, fHalfExtentY, fOrientation * 3.14159 / 180);
	}
	else if (sCollidableType == "circle")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());
		double fRadius = atof(pNode->first_attribute("radius")->value());

		pCollidable = new Circle(fPosX, fPosY, fRadius);
	}
	else if (sCollidableType == "tyre")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());

		pCollidable = new Tyre(fPosX, fPosY);
	}
	else if (sCollidableType == "box")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());
		double fSize = atof(pNode->first_attribute("size")->value());
		double fOrientation = atof(pNode->first_attribute("orientation")->value());

		pCollidable = new Box(fPosX, fPosY, fSize, fOrientation * 3.14159 / 180);
	}

	// Sets object's texture.
	pCollidable->setTexture(m_pTextureManager->getTexturePointer(sCollidableType));
	return pCollidable;
}

CollidableFactory::~CollidableFactory()
{
}

