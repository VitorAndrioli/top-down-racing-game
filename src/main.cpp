/**
\file main.cpp
*/

#include <SFML/Graphics.hpp>
#include "game.h"
#include "menu.h"
#include <iostream>
#include <array>

#include <string>
#include <fstream>
#include <streambuf>


using namespace sf;
int main()
{

	RenderWindow window(VideoMode(700, 700), "IMAT2605 Course work");
	window.setVerticalSyncEnabled(true);

	Game game;
	game.setMenuSize(window.getSize().x, window.getSize().y);
	
	sf::View menuView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	menuView.setViewport(sf::FloatRect(0, 0, 1, 1));
	sf::View player1View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	sf::View player2View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

	sf::View mapView(sf::FloatRect(0, 0, 1500, 1600));
	mapView.setViewport(sf::FloatRect(0.8, 0, 0.2, 0.2));

	sf::View p1displayView;
	p1displayView.setSize(100, 100);
	p1displayView.setCenter(50, 50);
	
	sf::View p2displayView;
	p2displayView.setSize(100, 100);
	p2displayView.setCenter(50, 50);
	
	
	
	do
	{
		window.clear(Color::Green);
		window.setView(menuView);
		window.draw(game);
		window.display();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				return 0;
			}
			if (event.type == Event::KeyPressed)
				game.processKeyPress(event.key.code);
		}

	} while (!game.hasStarted());

	game.load();
	if (game.isMultiplayer())
	{
		player2View.setViewport(sf::FloatRect(0, 0, 0.5, 1));
		player2View.setSize(window.getSize().x / 2, window.getSize().y);
		p2displayView.setViewport(sf::FloatRect(0, 0, 0.3, 0.3));

		player1View.setViewport(sf::FloatRect(0.5, 0, 0.5, 1));
		player1View.setSize(window.getSize().x / 2, window.getSize().y);
		p1displayView.setViewport(sf::FloatRect(0.5, 0, 0.3, 0.3));

	}
	else
	{
		player1View.setViewport(sf::FloatRect(0, 0, 1, 1));
		player1View.setSize(window.getSize().x, window.getSize().y);
		p1displayView.setViewport(sf::FloatRect(0, 0, 0.3, 0.3));
	}

	Clock clock;
	int cout = 0;
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

		
		window.setView(player1View);
		player1View.setCenter(game.getP1Position());
		//player1View.setRotation(game.player1.getOrientation() * TO_DEGREES + 90);
		window.draw(game);

		window.setView(p1displayView);
		window.draw(*game.getP1Display());

		if (game.isMultiplayer())
		{
			window.setView(player2View);
			player2View.setCenter(game.getP2Position());
			window.draw(game);

			window.setView(p2displayView);
			window.draw(*game.getP2Display());

		}

		window.setView(mapView);
		window.draw(game);

		if (game.isPaused())
		{
			window.setView(menuView);
			window.draw(game.getInstructionsBackground());
			window.draw(game.getInstructions());
		}


		

		window.display();
	}

	return 0;
}