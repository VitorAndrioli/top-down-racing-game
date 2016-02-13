/**
\file main.cpp
*/

/*! \mainpage Course Work - IMAT2605
* \brief Brief explanation
* More details explanation
*/


#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>
#include <array>

using namespace sf;
int main()
{

	RenderWindow window(VideoMode(700, 600), "IMAT2605 Course work");
	
	Game game;

	sf::Texture tyreTexture;
	tyreTexture.loadFromFile("assets/img/tyre.jpg");
	game.tyre.m_sprite.setTexture(tyreTexture);

	sf::Texture texture;
	texture.loadFromFile("assets/img/track_small.jpg");
	
	// Create a sprite
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 1500, 1600));
	sprite.scale(2, 2);
	sprite.setColor(sf::Color(255, 255, 255, 200));
	sprite.setPosition(0, 0);
	
	sf::View mainView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	mainView.setViewport(sf::FloatRect(0, 0, 1, 1));

	sf::View miniView(sf::FloatRect(0, 0, 1500, 1600));
	miniView.setViewport(sf::FloatRect(0.8, 0, 0.2, 0.2));
	
	Clock clock;
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
				game.processKeyPress(event.key.code);
			if (event.type == Event::KeyReleased)
				game.processKeyRelease(event.key.code);
										
		}

		if (clock.getElapsedTime().asSeconds() > 0.0005)
		{
			game.update(clock.getElapsedTime().asSeconds());
			clock.restart();
		}

		window.clear(Color::Magenta);

		window.setView(mainView);
		//mainView.setCenter(game.car.getPosition().getX(), game.car.getPosition().getY());
		//window.draw(sprite);
		window.draw(game);

		//window.setView(miniView);
		//window.draw(sprite);
		//window.draw(game);
		

		window.display();
	}

	return 0;
}