#include "../../camera/header/hud.hpp"

HUD::HUD(sf::RenderWindow& window) : window(window), m_bulletTexture(), m_bullet(m_bulletTexture), m_bulletCount(font), m_distanceText(font)
{
	if (!m_bulletTexture.loadFromFile("Assets/Textures/TileSet/IndustrialPack/3 Objects/Fire-extinguisher1.png")) {
		throw std::runtime_error("Failed to load HUD bullet texture");
	}
	if (!font.openFromFile("Assets/Font/BitcountGridSingle_Roman-Regular.ttf")) {
		throw std::runtime_error("Failed to load HUD font");
	}

	m_bullet = sf::Sprite(m_bulletTexture);

	m_bullet.setScale(sf::Vector2f(3, 3));
	m_bullet.setOrigin(m_bullet.getLocalBounds().getCenter());
	m_bullet.setPosition(window.mapPixelToCoords(sf::Vector2i(40, 50)));
	m_bulletCount.setPosition(window.mapPixelToCoords(sf::Vector2i(60, 60)));
	m_distanceText.setPosition(window.mapPixelToCoords(sf::Vector2i(static_cast<int>(window.getSize().x - 50)/2, 50)));

	m_bulletCount.setFillColor(sf::Color::Black);
	m_distanceText.setFillColor(sf::Color::Black);
}

void HUD::update(int bulletCounter, int distance) {
	m_bulletCount.setString(" x " + std::to_string(bulletCounter));
	m_distanceText.setString(std::to_string(distance / 10) + " m");
	m_bullet.setPosition(window.mapPixelToCoords(sf::Vector2i(40, 50)));
	m_bulletCount.setPosition(window.mapPixelToCoords(sf::Vector2i(60, 60)));
	m_distanceText.setPosition(window.mapPixelToCoords(sf::Vector2i(static_cast<int>(window.getSize().x - 50)/2, 50)));
}

void HUD::draw() {
	window.draw(m_bulletCount);
	window.draw(m_bullet);
	window.draw(m_distanceText);
}