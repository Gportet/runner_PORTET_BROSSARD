#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
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

	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void collisionObstacle();
	void throwObject();
	void slide();
	void handleInput(const sf::Event& event);

};
