#include <SFML/Graphics.hpp>
#include "circle.h"
#include "car.h"
#include "collision.h"
#include "vector.h"
#include <iostream>
#include <array>

using namespace std;
int main()
{

	array<Circle, 5> tyres;
	array<OBB, 5> obbs;

	for (int i = 0; i < tyres.size(); i++)
	{
		tyres[i] = Circle(rand() % 800, rand() % 600, rand() % 50);
		obbs[i] = OBB(rand() % 800, rand() % 600, rand() % 40, rand() % 15, rand() % 360);
	}

	//OBB obb1(5, 7, 4, 2, 0);
	//OBB obb2(-3, 4, 3, 1, 0);

	Circle circle(400, 300, 20);
	//Circle circle2(100, 400, 12);
	Car car(208, 300, 30, 19, 0);
	Collision collision;

	
	sf::RenderWindow window(sf::VideoMode(800, 600), "IMAT2605 Course work");
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				car.moveRight();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				car.moveLeft();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				car.moveUp();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				car.moveDown();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				car.rotate();
			}
		}
		
		window.clear();
		window.draw(car);
		

		for (int i = 0; i < tyres.size(); i++)
		{
			window.draw(tyres[i]);
			window.draw(obbs[i]);
			collision.checkCollision(&car, &tyres[i]);
			collision.checkCollision(&car, &obbs[i]);
		}

		window.draw(circle);
		collision.checkCollision(&car, &circle);
		
		window.display();
	}

	return 0;
}