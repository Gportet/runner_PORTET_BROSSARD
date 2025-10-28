#pragma once

#include <SFML/Graphics.hpp>

class ParallaxLayer
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	float speed;
	float xOffset;
	
public:
	ParallaxLayer(const std::string& texturePath, float layerSpeed);
};

