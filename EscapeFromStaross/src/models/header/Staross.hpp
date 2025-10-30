#pragma once
#include <vector>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "../../camera/header/camera.hpp"
#include "../../models/header/Player.hpp"

class Staross
{
private:
	sf::Texture m_texture;
	sf::Vector2f m_speed;
	std::vector<sf::Sprite> m_sprites;

	float m_direction = 1;
	float m_posDestination;
	float m_randomPercentage;
	sf::RenderWindow& window;
	Camera& camera;
	Player& player;


public:
	Staross(sf::RenderWindow& window, Camera& camera, Player& p);

	void update();
	void draw();
	void move();
	sf::Sprite makeStar(sf::Vector2f origin, float radiusCenter, float radius, int points);
	void randomX(float min, float max);
	void rotate();
	void init();
	void updatePositionDestination();
};

