#pragma once

#include <SFML/Graphics.hpp>

class Platform
{
private:

	sf::Vector2f m_position;
	sf::RectangleShape m_shape;
	int floorInt;

public:

	Platform(float x,int fInt);

	sf::Vector2f getPosition();


};

