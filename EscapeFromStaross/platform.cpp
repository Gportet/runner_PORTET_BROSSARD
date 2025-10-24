#include "platform.h"

Platform::Platform(sf::Vector2f pos) : m_position(pos)
{
	m_shape.setSize(sf::Vector2f(1920, 50));
	m_shape.setFillColor(sf::Color::Red);
	m_shape.setPosition(m_position);
	 
}

sf::Vector2f Platform::getPosition()
{
	return m_position;
}

void Platform::draw(sf::RenderWindow& window) {
	window.draw(m_shape);
}