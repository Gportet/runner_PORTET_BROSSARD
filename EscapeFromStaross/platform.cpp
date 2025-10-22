#include "platform.h"

Platform::Platform(float x,int fInt) : floorInt(fInt)
{
	m_shape.setSize(sf::Vector2f(600, 150));
	m_shape.setFillColor(sf::Color::Red);
	int y = 0;
	switch (y) {
	case 1: y = 900; break;
	case 2: y = 600; break;
	case 3: y = 300; break;
	default: y = 0; break;
	}
	m_shape.setPosition(sf::Vector2f(x, y));
	 
}

sf::Vector2f Platform::getPosition()
{
	return m_position;
}