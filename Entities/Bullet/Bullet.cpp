#include "Bullet.h"



Bullet::Bullet(sf::Window* window,sf::Vector2f pos, float Direction, float Speed)
{
	setWindow(window);
	model.setPointCount(4);
	model.setPoint(0, sf::Vector2f(-10.0f, -10.0f));
	model.setPoint(1, sf::Vector2f(10.0f, -10.0f));
	model.setPoint(2, sf::Vector2f(10.0f, 10.0f));
	model.setPoint(3, sf::Vector2f(-10.0f, 10.0f));
	
	setInstance(this);

	model.setFillColor(sf::Color(0, 0, 0, 0));
	model.setOutlineColor(sf::Color(250, 250, 250));
	model.setOutlineThickness(1.0f);

	model.setPosition(pos);
	movement = sf::Vector2f(cos(Direction * 0.0174) * Speed, sin(Direction * 0.0174) * Speed);
	speed = Speed;

}
Bullet::~Bullet()
{

}

void Bullet::update()
{
	model.move(movement);
	model.rotate(speed / 2);
	
	

	if (wallCollision(model))
	{
		killObject();
	}
}

EntityManager<Bullet> bullet;