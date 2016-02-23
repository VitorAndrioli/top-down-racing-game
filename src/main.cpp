/*!
 * \file
 * \brief Entance point to software..
 */

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "game.h"
#include "menu.h"
#include <iostream>
#include <array>

#include <string>
#include <fstream>
#include <streambuf>

#define WINDOW_WIDTH 1200 //!< Window width.
#define WINDOW_HEIGHT 1000 //!< Window height.
#define TRACK_WIDTH 5386 //!< Window width.
#define TRACK_HEIGHT 5136 //!< Window height.

using namespace sf;

int main()
{
	// Instantiates window object.
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "IMAT2605 Course work");
	window.setVerticalSyncEnabled(true);

	// Instantiates game object.
	Game game;
	//  Sets menu size.
	game.setMenuSize(window.getSize().x, window.getSize().y);
	
	// Creates views.
	View menuView(FloatRect(0, 0, window.getSize().x, window.getSize().y)); // View for initial menu / instructions
	View player1View(FloatRect(0, 0, window.getSize().x, window.getSize().y)); //  View for first player.
	View player2View(FloatRect(0, 0, window.getSize().x, window.getSize().y)); // View for second player.
	View mapView(FloatRect(0, 0, TRACK_WIDTH, TRACK_HEIGHT)); // View for mini map.
	mapView.setViewport(FloatRect(0.78, 0.02, 0.2, 0.2)); // Puts mini map at top left.
	View p1displayView(FloatRect(0, 0, 60, 60)); // View for first player's velocimeter.
	View p2displayView(FloatRect(0, 0, 60, 60)); // View for second player's velocimeter.
	View clockView(FloatRect(0, 0, 200, 100)); // View for timer.
	clockView.setViewport(FloatRect(0.4, 0, 0.2, 0.2));

	// Main menu loop
	do
	{
		// Clear window and draw menu until game starts.
		window.clear(Color(43, 130, 62, 255));
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

	// Display loading screen.
	Font font;
	font.loadFromFile("./assets/font/GOTHICB.ttf");
	Text loading("Loading game...", font);
	loading.setCharacterSize(25);
	loading.setOrigin(loading.getGlobalBounds().width / 2, loading.getGlobalBounds().height/ 2);
	loading.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	window.clear(Color::Black);
	window.setView(menuView);
	window.draw(loading);
	window.display();

	// Load game.
	game.load();
	
	// If multiplayer, splits screen.
	if (game.isMultiplayer())
	{
		player2View.setViewport(FloatRect(0, 0, 0.499, 1));
		player2View.setSize(window.getSize().x / 2, window.getSize().y);
		p2displayView.setViewport(FloatRect(0.02, 0.8, 0.17, 0.17));

		player1View.setViewport(FloatRect(0.501, 0, 0.499, 1));
		player1View.setSize(window.getSize().x / 2, window.getSize().y);
		p1displayView.setViewport(FloatRect(0.52, 0.8, 0.17, 0.17));
	}
	else
	{
		player1View.setViewport(FloatRect(0, 0, 1, 1));
		player1View.setSize(window.getSize().x, window.getSize().y);
		p1displayView.setViewport(FloatRect(0.02, 0.8, 0.17, 0.17));
	}


	sf::Music backgroundMusic;
	backgroundMusic.openFromFile("./assets/sounds/music.wav");
	backgroundMusic.setLoop(true);
	backgroundMusic.play();


	Clock clock;

	// Game loop
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

		// Updates at 60 frames per second.
		if (clock.getElapsedTime().asSeconds() > 0.002f)
		{
			game.update(clock.restart().asSeconds());
		}

		window.clear(Color::White);

		// Draws player 1 view.
		window.setView(player1View);
		player1View.setCenter(game.getP1Position());
		window.draw(game);
		
		window.setView(p1displayView);
		window.draw(*game.getP1Display());
		
		// If multiplayer, draws player 2 view.
		if (game.isMultiplayer())
		{
			window.setView(player2View);
			player2View.setCenter(game.getP2Position());
			window.draw(game);

			window.setView(p2displayView);
			window.draw(*game.getP2Display());
		}
		
		// Draws mini map.
		window.setView(mapView);
		window.draw(game);

		// Draws timer.
		window.setView(clockView);
		window.draw(game.getTimer());

		// If paused, draw instructions.
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