#include <SFML/Graphics.hpp>
#include "circle.h"
#include "car.h"
#include "collision.h"
#include "vector2D.h"
#include <iostream>
#include <array>

using namespace std;
int main()
{

	array<Circle, 5> tyres;
	array<OBB, 5> obbs;

	for (int i = 0; i < tyres.size(); i++)
	{
		tyres[i] = Circle(rand() % 800, rand() % 800, rand() % 50, 0);
		obbs[i] = OBB(rand() % 800, rand() % 800, rand() % 40, rand() % 15, rand() % 360);
	}

	Car car(200, 300, 30, 19, 0);

	Circle circle(300, 300, 30, 0);
	Collision collision;
	
	sf::Clock clock;
	
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "IMAT2605 Course work");
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();



			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up) car.accelerate();
				if (event.key.code == sf::Keyboard::Down) car.reverse();
				if (event.key.code == sf::Keyboard::Right) car.turnRight();
				if (event.key.code == sf::Keyboard::Left) car.turnLeft();
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) car.decelerate();
			}
										
		}

		sf::Time elapsed = clock.restart();
		
		window.clear();
		car.update(elapsed);
		window.draw(car);
		
		circle.update(elapsed);
		window.draw(circle);

		collision.checkCollision(&car, &circle);

		for (int i = 0; i < tyres.size(); i++)
		{
			tyres[i].update(elapsed);
			obbs[i].update(elapsed);
			window.draw(tyres[i]);
			window.draw(obbs[i]);
			collision.checkCollision(&car, &tyres[i]);
			collision.checkCollision(&car, &obbs[i]);
		}

		
		window.display();
	}

	return 0;
}