#pragma once
#include <vector>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Player.h"

class Staross
{
private:
	sf::Vector2f m_speed;
	std::vector<sf::ConvexShape> m_shapes;
	sf::Vector2f m_distMax;
	sf::Vector2f m_distMin;
	float m_direction = 1;
	float m_posDestination;
	sf::RenderWindow& window;
	Player player;


public:
	Staross(Player p, sf::RenderWindow& window);

	void update();
	void draw();
	void move();
	sf::ConvexShape makeStar(sf::Vector2f origin, float radiusCenter, float radius, int points);
	float randomX(float min, float max);
	void rotate();
	void init();
};

