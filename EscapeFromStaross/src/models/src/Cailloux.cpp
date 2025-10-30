#include "../../models/header/Cailloux.hpp"

Cailloux::Cailloux(sf::Vector2f position) : m_texture(), m_sprite(m_texture) {
	if (!m_texture.loadFromFile("Assets/Textures/TileSet/IndustrialPack/3 Objects/Fire-extinguisher3.png")) {
		throw std::runtime_error("Failed to load bullet texture");
	}
	m_sprite = sf::Sprite(m_texture);

	m_sprite.setScale(sf::Vector2f(2, 2));
	m_sprite.setOrigin(m_sprite.getLocalBounds().getCenter());
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
	m_sprite.setPosition(m_position);
	window.draw(m_sprite);
}

sf::FloatRect Cailloux::getGlobalBounds() {
	return m_sprite.getGlobalBounds();
}

