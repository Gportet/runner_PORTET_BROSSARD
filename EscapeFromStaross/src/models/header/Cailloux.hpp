#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
class Cailloux 
{
private :
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_speed;
	sf::Vector2f m_position;
	bool m_isColliding = false;
	float m_collisionTimer = 3.f;


public:
	Cailloux(sf::Vector2f position);
	~Cailloux();

	void update();
	void collision();
	void Colliding();
	bool shouldBeRemoved() const;
	void draw(sf::RenderWindow& window);
	sf::FloatRect getGlobalBounds();
};

