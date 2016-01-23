/**
@file game.cpp
*/

#include "game.h"

using namespace std;

Game::Game()
{

	car = Car(50, 300, 0);
	
	circle = Circle(350, 300, 30, 0);
	obb = OBB(500, 300, 50, 15, 15);

}

void Game::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(car);
	target.draw(circle);
	target.draw(obb);
}

void Game::update(float timestep)
{
	car.update(timestep);
	circle.update(timestep);
	obb.update(timestep);
	collision.checkCollision(&car, &circle);
	collision.checkCollision(&car, &obb);
	collision.checkCollision(&circle, &obb);
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
