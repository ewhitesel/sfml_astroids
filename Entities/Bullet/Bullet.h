#pragma once
#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include "Collision/Collider.h"
#include "Entities/Object.h"
class Bullet : public Object, public Collider
{
private:
	sf::Vector2f movement;
	float speed;


public:
	Bullet(sf::Window* window, sf::Vector2f pos, float Direction, float Speed);
	~Bullet();
	void update();
};

extern EntityManager<Bullet> bullet;

#endif