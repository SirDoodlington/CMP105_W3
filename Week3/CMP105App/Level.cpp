#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	rectangle.setSize(sf::Vector2f(50, 50));
	rectangle.setFillColor(sf::Color::Magenta);
	rectangle.setPosition(300, 200);

	speed = 200;
	direction = 0;
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{

}

// Update game objects
void Level::update(float dt)
{
	float movement = speed * dt;

	if (direction == 0)
	{
		if (rectangle.getPosition().x + movement >= window->getSize().x - rectangle.getSize().x)
		{
			direction = 1;
		}
	}
	else
	{
		if (rectangle.getPosition().x - movement <= 0)
		{
			direction = 0;
		}
	}

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
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(rectangle);
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