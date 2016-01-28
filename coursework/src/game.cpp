/**
@file game.cpp
*/

#include "game.h"

using namespace std;

Game::Game()
{

	car = Car(50, 50, 0);
	ptr_circle2 = new Circle(200, 300, 50, 0);
	ptr_circle = new Circle(350, 290, 30, 0);
	//ptr_obb = new OBB(600, 310, 70, 15, 90);
	/*obstacles.at(0) = new Circle(350, 300, 30, 0);
	obstacles.at(1) = new Circle(400, 310, 30, 0);
	obstacles.at(2) = new Circle(400, 290, 30, 0);
	obstacles.at(3) = new OBB(500, 100, 50, 15, 15);
	obstacles.at(4) = new OBB(500, 600, 70, 15, 90);*/
	
	
}

void Game::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(car);
	/*target.draw(*ptr_circle);
	target.draw(*ptr_circle2);
	target.draw(*ptr_obb);
	
	/*for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		target.draw(*(*it));
	}*/
	
}

void Game::update(float timestep)
{
	car.update(timestep);
	//car.print();
	/*ptr_circle->update(timestep);
	ptr_circle2->update(timestep);
	ptr_obb->update(timestep);
	

	collision.checkCollision(&car, ptr_circle);
	collision.checkCollision(&car, ptr_circle2);
	collision.checkCollision(&car, ptr_obb);

	collision.checkCollision(ptr_circle, ptr_circle2);
	collision.checkCollision(ptr_circle, ptr_obb);

	collision.checkCollision(ptr_circle2, ptr_obb);

	
	/*for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
	{
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
	}*/


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
	if (code == sf::Keyboard::Right || code == sf::Keyboard::Left) car.stopTurning();
}
