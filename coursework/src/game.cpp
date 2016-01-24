/**
@file game.cpp
*/

#include "game.h"

using namespace std;

Game::Game()
{

	car = Car(50, 300, 0);
	circle = Circle(0, 0, 50, 0);
	ptr_circle = new Circle(350, 300, 30, 0);
	obstacles.at(0) = new Circle(350, 300, 30, 0);
	obstacles.at(1) = new Circle(400, 310, 30, 0);
	obstacles.at(2) = new Circle(400, 290, 30, 0);
	obstacles.at(3) = new OBB(500, 100, 50, 15, 15);
	obstacles.at(4) = new OBB(500, 600, 70, 15, 90);
	
	
}

void Game::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(car);
	for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		target.draw(*(*it));
	}
	
}

void Game::update(float timestep)
{
	car.updatePoints();
	car.update(timestep);
	for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		(*it)->updatePoints();
		(*it)->update(timestep);
	}

	for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		for (auto it2 = obstacles.begin(); it2 != obstacles.end(); ++it2)
		{
			if (it2 != it)
			{
				collision.checkCollision(*it, *it2);
			}
		}
	}


}

void Game::processKeyPress(Keyboard::Key code)
{
	if (code == sf::Keyboard::Up) car.accelerate();
	if (code == sf::Keyboard::Down) car.reverse();
	if (code == sf::Keyboard::Right) car.turnRight();
	if (code == sf::Keyboard::Left) car.turnLeft();
}

void Game::processKeyRelease(Keyboard::Key code)
{
	if (code == sf::Keyboard::Up || code == sf::Keyboard::Down) car.decelerate();
}
