#pragma once
#include <SFML/Graphics.hpp>

class Floor
{
public:
    Floor(float y, float segmentWidth, float segmentHeight);

    void draw(sf::RenderWindow& window);
    float getY() const;

private:
    sf::Texture m_texture;
    float m_y;
    float m_segmentWidth;
    float m_segmentHeight;
    sf::RectangleShape m_shape;
  
};
