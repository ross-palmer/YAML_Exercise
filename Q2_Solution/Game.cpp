#include "Game.h"
#include <iostream>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "SFML Playground", sf::Style::Default)
{
	m_window.setVerticalSyncEnabled(true);

	// Load the player tank
	if (!m_tankTexture.loadFromFile("E-100.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	LevelLoader::load(1, m_levelData);
	// Loop through our sequence of tank data 
	for (int i = 0; i < m_levelData.m_tanks.size(); i++)
	{
		sf::Sprite tankSprite;
		tankSprite.setTexture(m_tankTexture);
		// Set origin to the centre of the sprite
		tankSprite.setOrigin(m_tankTexture.getSize().x / 2.0, m_tankTexture.getSize().y / 2.0);
		// Set the tank position from the loaded level data
		tankSprite.setPosition(m_levelData.m_tanks.at(i).m_x, m_levelData.m_tanks.at(i).m_y);
		// Set the tank rotation 
		tankSprite.setRotation(m_levelData.m_tanks.at(i).m_rotation);
		// Set the tank x and y scaling factor 
		tankSprite.setScale(
			sf::Vector2f(m_levelData.m_tanks.at(i).m_scale, m_levelData.m_tanks.at(i).m_scale) );
		
		// Copy the sprite into the vector (sprite is appended)
		m_spriteVector.push_back(tankSprite);
	}

}

////////////////////////////////////////////////////////////
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(lag);
			lag -= MS_PER_UPDATE;
		}
		update(lag);

		render();
	}
}

////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

////////////////////////////////////////////////////////////
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;
		case sf::Keyboard::Up:
			// Up key was pressed...
			break;
		default:
			break;
		}
	}
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{

}

////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));

	// Render your sprites here....
	for (int i = 0; i < m_spriteVector.size(); i++)
	{
		m_window.draw(m_spriteVector.at(i));
	}

	m_window.display();
}





