#include "Cailloux.h"

Cailloux::Cailloux(sf::Vector2f position) {
	m_shape = sf::CircleShape(10.f);
	m_position = position;
	m_speed = sf::Vector2f(50, 0);
}

Cailloux::~Cailloux()
{
}

void Cailloux::update(sf::RenderWindow& window) {
	m_position += m_speed;
	draw(window);
}

void Cailloux::collision()
{
}

void Cailloux::draw(sf::RenderWindow& window) {
	m_shape.setPosition(m_position);
	window.draw(m_shape);
}