#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	rectangle.setSize(sf::Vector2f(50, 50));
	rectangle.setFillColor(sf::Color::Magenta);
	rectangle.setPosition(300, 200);

	playerCircle.setRadius(15);
	playerCircle.setFillColor(sf::Color::Green);
	playerCircle.setPosition(sf::Vector2f(100, 100));

	speed = 200;
	direction = 0;

	circVert = 0;
	circHori = 0;
}

Level::~Level()
{
	
}

// handle user input
void Level::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::W))
	{
		circVert = 1;
	}
	else if (input->isKeyDown(sf::Keyboard::S))
	{
		circVert = 2;
	}
	else
	{
		circVert = 0;
	}
	if (input->isKeyDown(sf::Keyboard::A))
	{
		circHori = 1;
	}
	else if (input->isKeyDown(sf::Keyboard::D))
	{
		circHori = 2;
	}
	else
	{
		circHori = 0;
	}
}

// Update game objects
void Level::update(float dt)
{
	float movement = speed * dt;

	//Rectangle movement
	if (direction == 0)
	{
		rectangle.setPosition(rectangle.getPosition().x + movement, rectangle.getPosition().y);
		if (rectangle.getPosition().x >= window->getSize().x - rectangle.getSize().x)
		{
			direction = 1;
			rectangle.setPosition(sf::Vector2f(window->getSize().x - rectangle.getSize().x, rectangle.getPosition().y));
		}
	}
	else
	{
		rectangle.setPosition(rectangle.getPosition().x - movement, rectangle.getPosition().y);
		if (rectangle.getPosition().x <= 0)
		{
			direction = 0;
			rectangle.setPosition(sf::Vector2f(0, rectangle.getPosition().y));
		}
	}

	//Player circle movement
	switch (circVert)
	{
	case 1:
		playerCircle.setPosition(playerCircle.getPosition().x, playerCircle.getPosition().y - movement);
		break;
	case 2:
		playerCircle.setPosition(playerCircle.getPosition().x, playerCircle.getPosition().y + movement);
		break;
	}

	switch (circHori)
	{
	case 1:
		playerCircle.setPosition(playerCircle.getPosition().x - movement, playerCircle.getPosition().y);
		break;
	case 2:
		playerCircle.setPosition(playerCircle.getPosition().x + movement, playerCircle.getPosition().y);
		break;
	}

	//Controlling the boundaries
	if (playerCircle.getPosition().x < 0)
	{
		playerCircle.setPosition(sf::Vector2f(0, playerCircle.getPosition().y));
	}
	if (playerCircle.getPosition().x + 2*playerCircle.getRadius() > window->getSize().x)
	{
		playerCircle.setPosition(sf::Vector2f(window->getSize().x - 2*playerCircle.getRadius(), playerCircle.getPosition().y));
	}
	if (playerCircle.getPosition().y < 0)
	{
		playerCircle.setPosition(sf::Vector2f(playerCircle.getPosition().x, 0));
	}
	if (playerCircle.getPosition().y + 2*playerCircle.getRadius() > window->getSize().y)
	{
		playerCircle.setPosition(sf::Vector2f(playerCircle.getPosition().x, window->getSize().y - 2*playerCircle.getRadius()));
	}
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(rectangle);
	window->draw(playerCircle);
	endDraw();
}

// clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}