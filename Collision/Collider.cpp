#include"Collider.h"


struct Line
{
	sf::Vector2f Initial;
	sf::Vector2f Terminal;
};

float Collider::getDistance(sf::Vector2f p1, sf::Vector2f p2)
{
	return (sqrt((pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2))));
}

sf::Vector2f Collider::getTransformedPoint(sf::ConvexShape object, int point)
{
	return (object.getTransform().transformPoint(object.getPoint(point)));
}


static std::vector<Object*>S_colideableObjects;

void Collider::setInstance(Object* instance) {

	S_colideableObjects.push_back((instance));
	current = instance;

}

Collider::~Collider()
{
	for (int i = 0; i < S_colideableObjects.size(); i++)
	{
		if (S_colideableObjects.at(i) == current)
		{
			S_colideableObjects.erase(S_colideableObjects.begin() + i);
			S_colideableObjects.shrink_to_fit();
		}
	}
}

bool Collider::collisionCheckRadius(sf::ConvexShape ship, sf::ConvexShape object)
{
	
	float shipRadius = getDistance(getTransformedPoint(ship, 3), ship.getPosition());
	float objectRadius = getDistance(getTransformedPoint(object, 3), object.getPosition());
	
	if (150 >= getDistance(ship.getPosition() , object.getPosition()))
	{		
		return true;
	}
	return false;
	
}

bool Collider::collisionSlope(sf::ConvexShape ship, sf::ConvexShape object)
{
	Line shipLine{};
	Line objectLine{};
	for (int p1 = 0; p1 < ship.getPointCount(); p1++)
	{
		for (int p2 = 0; p2 < object.getPointCount(); p2++)
		{

			if (p1 == 0)
			{
				shipLine.Initial = sf::Vector2f(getTransformedPoint(ship, p1));
				shipLine.Terminal = sf::Vector2f(getTransformedPoint(ship, ship.getPointCount() - 1));
			}
			else
			{
				shipLine.Initial = sf::Vector2f(getTransformedPoint(ship, p1));
				shipLine.Terminal = sf::Vector2f(getTransformedPoint(ship, p1 - 1));
			}
			if (p2 == 0)
			{
				objectLine.Initial = sf::Vector2f(getTransformedPoint(object, p2));
				objectLine.Terminal = sf::Vector2f(getTransformedPoint(object, object.getPointCount() - 1));
			}
			else
			{
				objectLine.Initial = sf::Vector2f(getTransformedPoint(object, p2));
				objectLine.Terminal = sf::Vector2f(getTransformedPoint(object, p2 - 1));
			}

			float shipSlope = ((shipLine.Initial).y - (shipLine.Terminal).y) / ((shipLine.Initial).x - (shipLine.Terminal).x);
			float objectSlope = ((objectLine.Initial).y - (objectLine.Terminal).y) / ((objectLine.Initial).x - (objectLine.Terminal).x);

			float shipYIntercept = shipLine.Initial.y - shipSlope * shipLine.Initial.x;
			float objectYIntercept = objectLine.Initial.y - objectSlope * objectLine.Initial.x;

			sf::Vector2f lineInterceptPoint = {};

			lineInterceptPoint.x = (shipYIntercept - objectYIntercept) / (objectSlope - shipSlope);
			lineInterceptPoint.y = shipSlope * lineInterceptPoint.x + shipYIntercept;


			if ((round(std::abs(getDistance(lineInterceptPoint, shipLine.Initial)) + std::abs(getDistance(lineInterceptPoint, shipLine.Terminal))) <= round(std::abs(getDistance(shipLine.Initial, shipLine.Terminal))) &&
				round(std::abs(getDistance(lineInterceptPoint, objectLine.Initial)) + std::abs(getDistance(lineInterceptPoint, objectLine.Terminal))) <= round(std::abs(getDistance(objectLine.Initial, objectLine.Terminal)))))
			{
				return true;
				
			}
		}
	}
	return false;
}

bool Collider::collisionCheck(sf::ConvexShape* shape)
{
	for (int object = 0; object < S_colideableObjects.size(); object++)
	{
		if (&S_colideableObjects.at(object)->model != shape)
		{
			if(collisionCheckRadius(*shape, S_colideableObjects.at(object)->model))
			{ 
				if (collisionSlope(*shape, S_colideableObjects.at(object)->model))
				{
					collisionSpecifics.collidedObject = S_colideableObjects.at(object);
					return true;
				}
			}
			
		}

	}
	return false;
	return 0;
}



bool Collider::wallCollision(sf::ConvexShape shape)
{
	if (shape.getPosition().x >= window->getSize().x)
	{
		return true;
	}
	if (shape.getPosition().x < 0)
	{
		return true;
	}
	if (shape.getPosition().y >= window->getSize().y)
	{
		return true;
	}
	if (shape.getPosition().y < 0)
	{
		return true;
	}
	return false;
}

void Collider::wallCollisionResolution(sf::ConvexShape* shape)
{
	if (shape->getPosition().x >= window->getSize().x)
	{
		shape->setPosition(0.1, shape->getPosition().y);
	}
	if (shape->getPosition().x < 0)
	{
		shape->setPosition(window->getSize().x, shape->getPosition().y);
	}
	if (shape->getPosition().y >= window->getSize().y)
	{
		shape->setPosition(shape->getPosition().x, 0.1);
	}
	if (shape->getPosition().y < 0)
	{
		shape->setPosition(shape->getPosition().x, window->getSize().y);
	}
}

