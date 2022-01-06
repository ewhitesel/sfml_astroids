#include "Astroid.h"

Astroid::Astroid(sf::Window* window,sf::Vector2f pos, sf::Vector2f Direction, float Speed,int Scale)
{
	setWindow(window);
	setInstance(this);
	model.setPointCount(8);
	model.setPoint(0, sf::Vector2f(0.75f, 1.0f));
	model.setPoint(1, sf::Vector2f(1.0f, 0.75f));
	model.setPoint(2, sf::Vector2f(1.0f, -0.75f));
	model.setPoint(3, sf::Vector2f(0.75f, -1.0f));
	model.setPoint(4, sf::Vector2f(-0.75f, -1.0f));
	model.setPoint(5, sf::Vector2f(-1.0f, -0.75f));
	model.setPoint(6, sf::Vector2f(-1.0f, 0.75f));
	model.setPoint(7, sf::Vector2f(-0.75f, 1.0f));
	model.setPosition(pos);
	direction = Direction;
	speed = Speed;
	scale = Scale;
	model.setScale(scale, scale);
	model.setFillColor(sf::Color(0, 0, 0, 0));
	model.setOutlineColor(sf::Color(100, 250, 50));
	model.setOutlineThickness(1.0f / scale);
	astroidWindow = window;
}
Astroid::~Astroid()
{
	if (scale > 20)
	{
		std::mt19937 randEngine(randD());
		std::uniform_real_distribution<double> rngDir(-1, 1);
		int amount = 2+rand()%6;
		for (int i = 0; i <= amount; i++)
		{
			direction = sf::Vector2f(rngDir(randEngine), rngDir(randEngine));
			astroid.create(astroidWindow, model.getTransform().transformPoint(model.getPoint(rand() % model.getPointCount())), direction, speed, scale / amount);
		}
	}
}

void Astroid::update()
{
	model.move(direction.x * speed, direction.y * speed);
	model.rotate(speed / 10);
	wallCollisionResolution(&model);
	if (collisionCheck(&model))
	{
			collisionSpecifics.collidedObject->killObject();
			killObject();
	}
}

EntityManager<Astroid> astroid;
