#pragma once

#include <SFML/Graphics.hpp>

class Platform
{
private:

	sf::Vector2f m_position;
	sf::RectangleShape m_shape;
	int floorInt;

public:

	Platform(sf::Vector2f pos);

	sf::Vector2f getPosition();

	void draw(sf::RenderWindow& window);

	sf::RectangleShape getShape();
};

