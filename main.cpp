

#include<SFML/Graphics.hpp>
#include"Entities/Astroid/Astroid.h"
#include"Entities/Bullet/Bullet.h"
#include"Entities/Player/Player.h"
#include<iostream>

int main()
{
	sf::Vector2i screenSize = sf::Vector2i(600,800);
	sf::Clock astroidGeneration;
	sf::RenderWindow window(sf::VideoMode(screenSize.y, screenSize.x), "SFML Game"); 
	window.setFramerateLimit(120);
	player.create(&window,sf::Vector2f(200, 200), 5.0f, 0.01f);
	std::random_device randD;
	std::mt19937 randEngine(randD());
	std::uniform_real_distribution<double> rngDir(-1, 1);
	std::uniform_real_distribution<double> rngPosX(0, window.getSize().x);
	std::uniform_real_distribution<double> rngPosY(0, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		if (astroidGeneration.getElapsedTime() >= sf::seconds(1.5))
		{
			
			sf::Vector2f direction = sf::Vector2f(rngDir(randEngine), rngDir(randEngine));
			sf::Vector2f position;
			if (direction.x > direction.y)
			{
				position = sf::Vector2f(0, rngPosY(randEngine));
			}
			else
			{
				position = sf::Vector2f(window.getSize().x, rngPosY(randEngine));
			}
			if (direction.y > direction.x)
			{
				position = sf::Vector2f(rngPosX(randEngine), 0);
			}
			else
			{
				position = sf::Vector2f(rngPosX(randEngine), window.getSize().y);
			}
			astroid.create(&window, position, direction, 0.5f + rand() % 4, 30 + rand() % 50);
			astroidGeneration.restart();
		}
		window.clear();
		for (int i = 0; player.returnInstance()[0]->returnList().size() > i; i++)
		{
			window.draw(player.returnInstance().at(0)->returnList().at(i)->model);
			player.returnInstance().at(0)->returnList().at(i)->update();	
		}
		window.display();
	}
	return 0;
}
