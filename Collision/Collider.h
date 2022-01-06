#pragma once
#ifndef COLLISION_H
#define COLLISION_H
#include <SFML/Graphics.hpp>
#include "Entities/Object.h"

struct CollisionCase
{
	bool collision = false;
	Object* collidedObject;
	void reset()
	{
		collision = false;
		collidedObject = NULL;
	}
};
class Collider
{
private:
	Object* current;
	sf::Window* window;
	float getDistance(sf::Vector2f p1, sf::Vector2f p2);
	sf::Vector2f getTransformedPoint(sf::ConvexShape object, int point);
public:
	CollisionCase collisionSpecifics;
	void setInstance(Object* instance);
	void setWindow(sf::Window* Window) { window = Window; }
	bool collisionCheckRadius(sf::ConvexShape ship, sf::ConvexShape object);
	
	bool collisionSlope(sf::ConvexShape ship, sf::ConvexShape object);
	bool collisionCheck(sf::ConvexShape* shape);


	bool wallCollision(sf::ConvexShape shape);
	void wallCollisionResolution(sf::ConvexShape *shape);
	
	~Collider();
};
#endif