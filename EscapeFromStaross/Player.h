#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Cailloux.h"
#include "ObjectManager.h"
class Player
{

private:
	sf::RectangleShape m_shape;
	sf::Vector2f m_speed;
	sf::Vector2f m_position;

public:
	//constructeur
	Player(sf::Vector2f position);
	~Player();

	void update();
	void draw(sf::RenderWindow& window);
	void collisionObstacle();
	void throwObject(ObjectManager& manager);
	void slide();
	void handleInput(const sf::Event& event, ObjectManager& manager);


	sf::Vector2f getPosition();

};
