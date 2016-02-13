/**
@file game.cpp
*/

#include "game.h"


using namespace std;

Game::Game()
{
	
	car = Car(50, 310, 0 * 3.14159 / 180);
	
	rapidxml::xml_document<> doc;
	ifstream file(".\\assets\\xml\\obstacles.xml");
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	string content(buffer.str());
	doc.parse<0>(&content[0]);
	rapidxml::xml_node<>* pRoot = doc.first_node();
	for (rapidxml::xml_node<> *pNode = pRoot->first_node("collidable"); pNode; pNode = pNode->next_sibling())
	{
		Collidable * newObstacle = CollidableFactory::NewCollidable(pNode);
		 if (newObstacle != NULL)
			obstacles.push_back(newObstacle);
		//*/
	}

}

void Game::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(car);
	for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		target.draw(**it);
	}
	
}

void Game::update(float timestep)
{
	car.update(timestep);
	//car.print();

	for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		(*it)->update(timestep);
	}

	for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		if (car.isMoving()) car.checkCollision(*it);
		for (auto it2 = obstacles.begin(); it2 != obstacles.end(); ++it2)
		{
			if (it2 != it)
			{
				if ((*it)->isMoving())
				{
					(*it)->checkCollision(*it2);
					(*it)->checkCollision(&car);
				}
				
			}
		}
	}


}

void Game::processKeyPress(Keyboard::Key code)
{
	if (code == sf::Keyboard::Up) car.m_bAccelerating = true;
	if (code == sf::Keyboard::Down) car.m_bReversing = true;
	if (code == sf::Keyboard::Right) car.m_bTurningRight = true;
	if (code == sf::Keyboard::Left) car.m_bTurningLeft = true;
	if (code == sf::Keyboard::Space) obstacles.back()->setVelocity(Vector2D<double>(0, 150)); //car.m_bBraking = true;
	//*/
	/*if (code == sf::Keyboard::Up) (obstacles.front())->setVelocity(Vector2D<double>(0, -150));
	if (code == sf::Keyboard::Down) (obstacles.front())->setVelocity(Vector2D<double>(0, 150));
	if (code == sf::Keyboard::Right) (obstacles.front())->setVelocity(Vector2D<double>(150, 0));
	if (code == sf::Keyboard::Left) (obstacles.front())->setVelocity(Vector2D<double>(-150, 0));
	//*/
}

void Game::processKeyRelease(Keyboard::Key code)
{
	if (code == sf::Keyboard::Up) car.m_bAccelerating = false;
	if (code == sf::Keyboard::Down) car.m_bReversing = false;
	if (code == sf::Keyboard::Right)  car.m_bTurningRight = false;
	if (code == sf::Keyboard::Left)  car.m_bTurningLeft = false;
	if (code == sf::Keyboard::Space) car.m_bBraking = false;
}
