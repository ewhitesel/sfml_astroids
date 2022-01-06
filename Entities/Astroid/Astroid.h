#pragma once
#ifndef ASTROID_H
#define ASTROID_H
#include <SFML/Graphics.hpp>
#include "Collision/Collider.h"
#include "Entities/Object.h"
#include<random>

class Astroid : public Object, public Collider
{
private:
	sf::Vector2f direction;
	float speed;
	int scale;
	sf::Window* astroidWindow;
	std::random_device randD;
public:

	Astroid(sf::Window* window, sf::Vector2f pos, sf::Vector2f Direction, float Speed, int Scale);
	~Astroid();
	void update();
};

extern EntityManager<Astroid> astroid;

#endif
