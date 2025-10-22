#pragma once
#include <SFML/Graphics.hpp>
class Cailloux
{
private :
	sf::CircleShape m_shape;
	sf::Vector2f m_speed;
	sf::Vector2f m_position;


public:
	Cailloux(sf::Vector2f position);
	~Cailloux();

	void update(sf::RenderWindow& window);
	void collision();
	void draw(sf::RenderWindow& window);
};

