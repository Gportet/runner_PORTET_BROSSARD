#include "../header/platform.hpp"

Platform::Platform(sf::Vector2f pos) : m_position(pos)
{
	if (!m_texture.loadFromFile("Assets/Textures/TileSet/IndustrialPack/1 Tiles/IndustrialTile_27.png")) {
		throw std::runtime_error("Failed to load platform texture");
	}
	m_shape.setTexture(&m_texture);
	m_shape.setSize(sf::Vector2f(1000, 100));
	m_shape.setPosition(m_position);
	 
}

sf::Vector2f Platform::getPosition()
{
	return m_position;
}

void Platform::draw(sf::RenderWindow& window) {
	window.draw(m_shape);
}

sf::RectangleShape Platform::getShape() {
	return m_shape;
}

void Platform::setSize(sf::Vector2f size)
{
	m_shape.setSize(size);
}
