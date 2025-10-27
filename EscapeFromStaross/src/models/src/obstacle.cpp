#include "../header/obstacle.hpp"

Obstacle::Obstacle(sf::Vector2f pos) : m_position(pos)
{
	m_shape.setSize(sf::Vector2f(100, 100));
	m_shape.setPosition(m_position);
}

void Obstacle::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
	//window.draw(*m_sprite);

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


