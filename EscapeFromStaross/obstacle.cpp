#include "obstacle.h"

Obstacle::Obstacle(sf::Vector2f position) : m_position(position)
{

}

void Obstacle::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
	window.draw(*m_sprite);
}

sf::FloatRect Obstacle::getGlobalBounds()
{
	return m_sprite->getGlobalBounds();
}

sf::Vector2f Obstacle::getPosition()
{
	return m_position;
}

sf::RectangleShape Obstacle::getShape()
{
	return m_shape;
}


