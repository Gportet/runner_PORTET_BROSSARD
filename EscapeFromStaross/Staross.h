#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

class Staross
{
private:
	sf::Vector2f m_speed;
	std::vector<sf::ConvexShape> m_shapes;

	Player player;


public:
	Staross(Player p);

	void update();
	void draw(sf::RenderWindow& window);

	sf::ConvexShape makeStar(sf::Vector2f origin, float radiusCenter, float radius, int points);
	void variationSpeed();


};

