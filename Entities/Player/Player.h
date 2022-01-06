#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "Collision/Collider.h"
#include "Entities/Object.h"
#include "Entities/Bullet/Bullet.h"
#include "Entities/Astroid/Astroid.h"

class Player : public Object, public Collider
{
private:
	sf::Vector2f force;
	float rotationSpeed;
	float speed;
	sf::Window* playerWindow;
	sf::Clock reloadTime;
public:
	Player(sf::Window* window, sf::Vector2f pos, float RotationSpeed, float Speed);
	~Player();
	void update();
};

extern EntityManager<Player> player;

#endif