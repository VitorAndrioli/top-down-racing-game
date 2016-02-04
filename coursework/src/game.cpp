/**
@file game.cpp
*/

#include "game.h"

using namespace std;

Game::Game()
{

	car = Car(50, 310, 0);
	obstacles.push_back(new Circle(350, 280, 30, 0));
	obstacles.push_back(new Circle(450, 260, 30, 0));
	/*obstacles.push_back(new Circle(420, 290, 30, 0));
	obstacles.push_back(new OBB(560, 300, 50, 15, 15));
	obstacles.push_back(new OBB(500, 600, 70, 15, 90));
	//*/
	
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
	for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		(*it)->update(timestep);
	}

	for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		car.checkCollision(*it);
		for (auto it2 = obstacles.begin(); it2 != obstacles.end(); ++it2)
		{
			if (it2 != it)
			{
				(*it)->checkCollision(*it2);
			}
		}
	}


}

void Game::processKeyPress(Keyboard::Key code)
{
	if (code == sf::Keyboard::Up) car.m_bAccelerating = true; //car.accelerate();
	if (code == sf::Keyboard::Down) car.m_bReversing = true; //car.reverse();
	if (code == sf::Keyboard::Right) car.m_bTurningRight = true;
	if (code == sf::Keyboard::Left) car.m_bTurningLeft = true;
}

void Game::processKeyRelease(Keyboard::Key code)
{
	if (code == sf::Keyboard::Up) car.m_bAccelerating = false;
	if (code == sf::Keyboard::Down) car.m_bReversing = false;
	if (code == sf::Keyboard::Right)  car.m_bTurningRight = false;
	if (code == sf::Keyboard::Left)  car.m_bTurningLeft = false;
}
