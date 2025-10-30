#include "../header/wall.hpp"

Wall::Wall(sf::Vector2f position) : Obstacle(position)
{
	if (!m_texture.loadFromFile("Assets/Textures/Obstacles/trashcan.png")) {
		std::cerr;
	}

	m_sprite = std::make_unique<sf::Sprite>(m_texture);
	m_sprite->setPosition(m_position);
	m_sprite->setScale(sf::Vector2f(0.3, 0.3));
}
