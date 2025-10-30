#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class HUD
{
private:
	sf::Font font;
	sf::Text m_distanceText;
	sf::Text m_bulletCount;
	sf::Texture m_bulletTexture;
	sf::Sprite m_bullet;
	sf::RenderWindow& window;
public:

	HUD(sf::RenderWindow& window);

	void update(int bulletCounter, int distance);

	void draw();
};

