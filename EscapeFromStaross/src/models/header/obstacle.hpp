#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Obstacle
{
protected:

	sf::Texture m_texture;

	sf::Vector2f m_position;

	sf::RectangleShape m_shape;

	std::unique_ptr<sf::Sprite> m_sprite;

public:

	Obstacle(sf::Vector2f position);

	void draw(sf::RenderWindow& window);

	sf::FloatRect getGlobalBounds();

	sf::Vector2f getPosition();

	sf::RectangleShape getShape();

};

