#include "../../models/header/Cailloux.hpp"

Cailloux::Cailloux(sf::Vector2f position) {
	m_shape = sf::CircleShape(10.f);
	m_shape.setFillColor(sf::Color::White);
	m_position = position;
	m_speed = sf::Vector2f(20,0);
}

Cailloux::~Cailloux()
{
}

void Cailloux::update() {
	if (!m_isColliding)
	{
		m_position += m_speed;
	}
	else
	{
		m_collisionTimer -= 1;
	}
}

void Cailloux::collision()
{
	m_shape.setFillColor(sf::Color::Red);
	Colliding();
}

void Cailloux::Colliding()
{
	m_isColliding = true;
}

bool Cailloux::shouldBeRemoved() const
{
	return m_isColliding && m_collisionTimer <= 0.f;
}

void Cailloux::draw(sf::RenderWindow& window) {
	m_shape.setPosition(m_position);
	window.draw(m_shape);
}

sf::FloatRect Cailloux::getGlobalBounds() {
	return m_shape.getGlobalBounds();
}

