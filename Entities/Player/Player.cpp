#include "Player.h"

Player::Player(sf::Window* window,sf::Vector2f pos, float RotationSpeed, float Speed)
{

	setWindow(window);
	float shipSize = 10;
	sf::Vector2f shipDimensions(17.0f, 10.0f);
	shipDimensions = shipDimensions + sf::Vector2f(shipSize, shipSize);
	model.setPointCount(3);
	model.setPoint(0, sf::Vector2f(0.0f, shipDimensions.y / 2));
	model.setPoint(1, sf::Vector2f(0.0f, -shipDimensions.y / 2));
	model.setPoint(2, sf::Vector2f(shipDimensions.x, 0.0f));
	model.setOrigin(5.78, 0);

	model.setFillColor(sf::Color(0, 0, 0, 0));
	model.setOutlineColor(sf::Color(250, 0, 0));
	model.setOutlineThickness(1.0f);

	setInstance(this);

	model.setPosition(pos);

	rotationSpeed = RotationSpeed;
	speed = Speed;
	playerWindow = window;
}
Player::~Player()
{
	playerWindow->close();
}

void Player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		force += sf::Vector2f(cos(model.getRotation() * 0.01743292) * speed, sin(model.getRotation() * 0.01743292) * speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		model.rotate(-rotationSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		model.rotate(rotationSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& reloadTime.getElapsedTime() >= sf::seconds(0.5))
	{
		bullet.create(playerWindow ,model.getPosition(), model.getRotation(), 5);
		reloadTime.restart();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)&& reloadTime.getElapsedTime() >= sf::seconds(0.5))
	{
		astroid.kill(0);
		reloadTime.restart();
	}
	model.move(force); 
	wallCollisionResolution(&model);
}

EntityManager<Player> player;
