/*!
* \file
* \brief Implementation of Car class.
*/

#include "game.h"

Game::Game() : m_bMultiPlayer(false), m_bPaused(true), m_fTimer(0)
{ 
}

/*!
 * Move instructions screen to the center of the window and calls setSize() method of main menu.
 *
 * \param fWidth,fHeight Width and height of the window.
 */
void Game::setMenuSize(const double fWidth, const double fHeight)
{
	m_instructions.move(fWidth / 2, fHeight / 2); // Centers instructions text.
	m_instructionsBackground.move(fWidth / 2, fHeight / 2); // Centers instructions background.
	m_menu.setSize(fWidth, fHeight);
}

/*!
 * Gets selected option from menu and starts the game.
 * Game starts paused to show the players the instructions.
 */
void Game::setMode()
{
	m_bMultiPlayer = m_menu.getOption();
	m_bStarted = true;
	m_bPaused = false;
}

/*!
 * Loads instructions text based on the game mode and creates its background.
 * Instantiate cars and use a Factory to, from a xml file, create every collidable object.
 * Assigns all the respective textures, using the Singleton Texture Manager.
 *
 */
void Game::load()
{	
	// Gets instance of Texture manager.
	TextureManager* pTextureManager = TextureManager::getInstance();
	// Instantiates a Collidable Factory.
	CollidableFactory collidableFactory;

	// Assigns background texture.
	m_background.setTexture(*pTextureManager->getTexturePointer("track"));
	m_background.scale(5386.f / m_background.getTexture()->getSize().x, 5136.f / m_background.getTexture()->getSize().y); // Scales texture to make sure it fits the car.


	// Read instructions from .txt file.
	std::string s_fontPath;
	if (m_bMultiPlayer) s_fontPath = "./assets/txt/instructions_multi_player.txt";
	else s_fontPath = "./assets/txt/instructions_single_payer.txt";
	std::ifstream instructionsFile(s_fontPath);
	std::string instructionsString((std::istreambuf_iterator<char>(instructionsFile)), std::istreambuf_iterator<char>());
	
	// Assign font, font size, string and origin to SFML text member variable.
	m_font.loadFromFile("./assets/font/GOTHICB.ttf");
	m_instructions.setFont(m_font);
	m_instructions.setCharacterSize(18);
	m_instructions.setString(instructionsString);
	m_instructions.setOrigin(m_instructions.getLocalBounds().width / 2, m_instructions.getLocalBounds().height / 2);

	// Assign font, font size, color and origin to SFML text timer member variable.
	m_timerText.setFont(m_font);
	m_timerText.setCharacterSize(45);
	m_timerText.setColor(Color(255, 207, 46));
	m_timerText.setOrigin(m_timerText.getLocalBounds().width / 2, m_timerText.getLocalBounds().height / 2);

	// Creates a semi-transparent backgrounf for instructions screen, based on its size (adding margins).
	m_instructionsBackground.setSize(Vector2f(m_instructions.getLocalBounds().width + 15, m_instructions.getLocalBounds().height + 25));
	m_instructionsBackground.setFillColor(Color(0, 0, 0, 120));
	m_instructionsBackground.setOrigin(m_instructionsBackground.getSize().x / 2, m_instructionsBackground.getSize().y / 2);

	// Instantiantes first player and, if necessary, second player. Assigns their textures.
	player1 = new Car(3780, 3141, -90 * TO_RADIANS);
	player1->setTexture(pTextureManager->getTexturePointer("car_01"));
	player1->setWheelTexture(pTextureManager->getTexturePointer("car_tyre"));
	
	if (m_bMultiPlayer)
	{
		player2 = new Car(3620, 3141, -90 * TO_RADIANS);
		player2->setTexture(pTextureManager->getTexturePointer("car_02"));
		player2->setWheelTexture(pTextureManager->getTexturePointer("car_tyre"));
	}

	
	// Read xml file to get details of every collidable to be created.	
	rapidxml::xml_document<> doc;
	ifstream file("./assets/xml/collidables.xml");
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	string content(buffer.str());
	doc.parse<0>(&content[0]);
	rapidxml::xml_node<>* pRoot = doc.first_node();
	for (rapidxml::xml_node<> *pNode = pRoot->first_node("collidable"); pNode; pNode = pNode->next_sibling())
	{
		// For every xml node, create a new collidable.
		Collidable* newObstacle = collidableFactory.makeCollidable(pNode);
		if (newObstacle != NULL) m_pvCollidables.push_back(newObstacle);
	}
}

/*!
 * If the game has not yet started, draws the main menu. Else, draws the background, cars and collidable objects.
 * 
 * \param target Target to which draw the sprite.
 * \param states States used for drawing to a RenderTarget.
 */
void Game::draw(RenderTarget &target, RenderStates states) const
{
	if (!m_bStarted) target.draw(m_menu);
	else 
	{
		target.draw(m_background);
		target.draw(*player1);
		if (m_bMultiPlayer) target.draw(*player2);
		for (auto it = m_pvCollidables.begin(); it != m_pvCollidables.end(); ++it) target.draw(**it);
	}
}

/*!
 * If game is paused, objects are not updated.
 * Else, updates and checks for collision with other collidables. 
 * Collision tests are only performed if the object has moved since last frame, to avoid processing waste.
 */
void Game::update(float timestep)
{

	// If paused, exits method.
	if (m_bPaused) return;
	
	// Updates timer
	m_fTimer += timestep;
	sprintf_s<sizeof(timerBuffer)>(timerBuffer, "%02.0f:%02.0f:%02.0f", floor(m_fTimer / 3600.0), floor(fmod(m_fTimer, 3600.0) / 60.0), floor(fmod(m_fTimer, 60.0)));
	m_timerText.setString(timerBuffer);
	
	// Updates first player.
	player1->update(timestep);
	
	// If multi player mode is on, updates second player and check for collisions between the cars.
	if (m_bMultiPlayer)
	{
		player2->update(timestep);
		if (player1->moved()) player1->checkCollision(player2);
		if (player2->moved()) player2->checkCollision(player1);
	}
	
	// Iterates through every collidable, updates it and check for collisions with other collidables.
	for (auto collidable_it1 = m_pvCollidables.begin(); collidable_it1 != m_pvCollidables.end(); ++collidable_it1)
	{
		// Updates.
		(*collidable_it1)->update(timestep);
		// Check for collisions with cars if they have moved.
		if (player1->moved())	player1->checkCollision(*collidable_it1);
		if (m_bMultiPlayer && player2->moved()) player2->checkCollision(*collidable_it1);
		
		// Check if collidable has moved since last frame.
		if ((*collidable_it1)->moved())
		{
			// If so, checks collision with cars.
			player1->checkCollision(*collidable_it1);
			if (m_bMultiPlayer) player2->checkCollision(*collidable_it1);
			
			// Iterates again through every collidable checking for collision.
			for (auto it2 = m_pvCollidables.begin(); it2 != m_pvCollidables.end(); ++it2)
			{
				if (it2 != collidable_it1) (*collidable_it1)->checkCollision(*it2);
			}
		}
	}
}

/*!
 * Ensures objects are not affected when game is paused and that no null pointer is used.
 */
void Game::processKeyPress(Keyboard::Key code)
{
	if (!m_bStarted)
	{
		if (code == Keyboard::Up || code == Keyboard::Down)	if (m_bPaused) m_menu.toggleOptions();
		if (code == Keyboard::Return) setMode();
	}
	else
	{
		if (code == Keyboard::P) m_bPaused = !m_bPaused;

		if (!m_bPaused)
		{
			if (code == Keyboard::Up) player1->m_bAccelerating = true;
			if (code == Keyboard::Down)	player1->m_bReversing = true;
			if (code == Keyboard::Right) player1->m_bTurningRight = true;
			if (code == Keyboard::Left) player1->m_bTurningLeft = true;
			

			if (m_bMultiPlayer)
			{
				if (code == Keyboard::RControl) player1->m_bBraking = true;

				if (code == Keyboard::W) player2->m_bAccelerating = true;
				if (code == Keyboard::S) player2->m_bReversing = true;
				if (code == Keyboard::D)  player2->m_bTurningRight = true;
				if (code == Keyboard::A)  player2->m_bTurningLeft = true;
				if (code == Keyboard::LControl) player2->m_bBraking = true;
			}
			else {
				if (code == Keyboard::Space) player1->m_bBraking = true;
			}
		}
	}
}

/*!
* Ensures objects are not affected when game is paused and that no null pointer is used.
*/
void Game::processKeyRelease(Keyboard::Key code)
{
	if (m_bStarted)
	{
		if (!m_bPaused)
		{
			if (code == Keyboard::Up) player1->m_bAccelerating = false;
			if (code == Keyboard::Down)	player1->m_bReversing = false;
			if (code == Keyboard::Right) player1->m_bTurningRight = false;
			if (code == Keyboard::Left) player1->m_bTurningLeft = false;
			

			if (m_bMultiPlayer)
			{
				if (code == Keyboard::RControl) player1->m_bBraking = false;

				if (code == Keyboard::W) player2->m_bAccelerating = false;
				if (code == Keyboard::S) player2->m_bReversing = false;
				if (code == Keyboard::D)  player2->m_bTurningRight = false;
				if (code == Keyboard::A)  player2->m_bTurningLeft = false;
				if (code == Keyboard::LControl) player2->m_bBraking = false;
			}
			else {
				if (code == Keyboard::Space) player1->m_bBraking = false;
			}
		}
	}
}

bool Game::isPaused()
{
	return m_bPaused;
}
bool Game::hasStarted()
{
	return m_bStarted;
}
bool Game::isMultiplayer()
{
	return m_bMultiPlayer;
}

// Setters and getters
Vector2f Game::getP1Position()
{
	return Vector2f(player1->getPosition().getX(), player1->getPosition().getY());
}

Vector2f Game::getP2Position()
{
	return Vector2f(player2->getPosition().getX(), player2->getPosition().getY());
}

RectangleShape Game::getInstructionsBackground()
{
	return m_instructionsBackground;
}

Text Game::getInstructions()
{
	return m_instructions;
}

Text Game::getTimer()
{
	return m_timerText;
}

CarDisplay* Game::getP1Display()
{
	return player1->getDisplay();
}

CarDisplay* Game::getP2Display()
{
	return player2->getDisplay();
}