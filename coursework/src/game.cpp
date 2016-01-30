/**
@file game.cpp
*/

#include "game.h"

using namespace std;

Game::Game()
{

	car = Car(350, 300, 0);
	/*obstacles.push_back(new Circle(350, 200, 30, 0));
	obstacles.push_back(new Circle(400, 40, 30, 0));
	obstacles.push_back(new Circle(420, 290, 30, 0));
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
		for (auto it2 = obstacles.begin(); it2 != obstacles.end(); ++it2)
		{
			if (it2 != it)
			{
				car.checkCollision(*it2);
				(*it)->checkCollision(*it2);
			}
		}
	}


}

void Game::processKeyPress(Keyboard::Key code)
{
	if (code == sf::Keyboard::Up) car.accelerate();
	if (code == sf::Keyboard::Down) car.reverse();
	if (code == sf::Keyboard::Right) car.m_bTurningRight = true; //car.turnRight();
	if (code == sf::Keyboard::Left) car.m_bTurningLeft = true; //car.turnLeft();
}

void Game::processKeyRelease(Keyboard::Key code)
{
	if (code == sf::Keyboard::Up) car.m_bAccelerating = false; //car.decelerate();
	if (code == sf::Keyboard::Down) car.m_bReversing = false; //car.decelerate();
	if (code == sf::Keyboard::Right)  car.m_bTurningRight = false;//car.stopTurning();
	if (code == sf::Keyboard::Left)  car.m_bTurningLeft = false;//car.stopTurning();
}
