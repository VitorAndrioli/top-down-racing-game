#include "collidableFactory.h"

Collidable * CollidableFactory::NewCollidable(const rapidxml::xml_node<>* pNode)
{
	string sCollidableType = pNode->first_attribute("type")->value();

	if (sCollidableType == "obb")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());
		double fHalfExtentX = atof(pNode->first_attribute("halfExtentX")->value());
		double fHalfExtentY = atof(pNode->first_attribute("halfExtentY")->value());
		double fOrientation = atof(pNode->first_attribute("orientation")->value());

		return new OBB(fPosX, fPosY, fHalfExtentX, fHalfExtentY, fOrientation * 3.14159 / 180);
	}
	if (sCollidableType == "circle")
	{
		double fPosX = atof(pNode->first_attribute("posX")->value());
		double fPosY = atof(pNode->first_attribute("posY")->value());
		double fRadius = atof(pNode->first_attribute("radius")->value());
		double fOrientation = atof(pNode->first_attribute("orientation")->value());

		return new Circle(fPosX, fPosY, fRadius, fOrientation);
	}
	return NULL;


}

Collidable * CollidableFactory::NewCollidable(const std::string &description)
{

	cout << description << endl;

	string type;

	//split(description, ';');

	if (description == "obb")
		return new OBB(450, 300, 20, 200, 180 * 3.14159 / 180);
	if (description == "circle")
		return new Circle(300, 300, 25, 0);
	return NULL;
}


string CollidableFactory::split(const std::string parameter, char delim) {
	/*std::stringstream ss(parameter);
	std::string item;
	while (std::getline(ss, item, delim)) {
		cout << item << endl;
	}*/

	return "test";
}