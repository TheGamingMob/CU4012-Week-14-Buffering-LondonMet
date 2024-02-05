#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	circle.setRadius(15);
	circle.setPosition(300, 300);
	circle.setFillColor(sf::Color::Green);
	circle.setOutlineColor(sf::Color::Magenta);
	circle.setOutlineThickness(2.f);

	Player.setSize(sf::Vector2f(50, 50));
	Player.setFillColor(sf::Color::Red);
	Player.setOutlineColor(sf::Color::Black);
	Player.setOutlineThickness(5.f);
	Player.setPosition(100, 100);

	bouncingShape.setRadius(30);
	bouncingShape.setPosition(150, 150);
	bouncingShape.setFillColor(sf::Color::Blue);
	bouncingShape.setOutlineColor(sf::Color::Yellow);
	bouncingShape.setOutlineThickness(2.f);


	bouncingShapeX = 300;
	bouncingShapeY = 300;
	speed = 300;
	PlayerSpeed = 300;
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::W))
	{
		//input->setKeyUp(sf::Keyboard::W);
		Player.move(0, -PlayerSpeed * dt);
	}
	if (input->isKeyDown(sf::Keyboard::A))
	{
		//input->setKeyUp(sf::Keyboard::A);
		Player.move(-PlayerSpeed * dt, 0);
	}
	if (input->isKeyDown(sf::Keyboard::S))
	{
		//input->setKeyUp(sf::Keyboard::S);
		Player.move(0, PlayerSpeed * dt);
	}
	if (input->isKeyDown(sf::Keyboard::D))
	{
		//input->setKeyUp(sf::Keyboard::D);
		Player.move(PlayerSpeed * dt, 0);
	}

	if (input->isKeyDown(sf::Keyboard::Add))
	{
		input->setKeyUp(sf::Keyboard::Add);
		bouncingShapeX += 300.f;
		bouncingShapeY += 300.f;
	}
}

// Update game objects
void Level::update(float dt)
{
	circle.move(speed * dt, 0);
	if (circle.getPosition().x < window->getSize().x - circle.getRadius())
	{
		speed = speed;
	}
	else
		speed = -speed;
	if (circle.getPosition().x <= 0)
	{
		speed = -speed;
	}
	sf::Vector2f pos = Player.getPosition();
	sf::Vector2f size = Player.getSize();

	if (pos.x > window->getSize().x - size.x)
	{
		pos.x = window->getSize().x - size.x;
	}
	if (pos.x < 0)
	{
		pos.x = 0;
	}
	if (pos.y > window->getSize().y - size.y)
	{
		pos.y = window->getSize().y - size.y;
	}
	if (pos.y < 0)
	{
		pos.y = 0;
	}
	Player.setPosition(pos);

	bouncingShape.move(bouncingShapeX * dt, bouncingShapeY * dt);

	if (bouncingShape.getPosition().x <= 0 ||
		bouncingShape.getPosition().x >= window->getSize().x - bouncingShape.getRadius() * 2)
	{
		bouncingShapeX = -bouncingShapeX;
	}
	if (bouncingShape.getPosition().y <= 0 ||
		bouncingShape.getPosition().y >= window->getSize().y - bouncingShape.getRadius() * 2)
	{
		bouncingShapeY = -bouncingShapeY;
	}
}
// Render level
void Level::render()
{
	beginDraw();
	window->draw(circle);
	window->draw(Player);
	window->draw(bouncingShape);
	endDraw();
}

