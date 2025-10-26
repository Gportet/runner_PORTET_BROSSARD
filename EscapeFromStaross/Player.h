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
	sf::Vector2f max_speed;
	sf::Vector2f m_position;
	int m_projectiles = 5;
	float m_projTimer = 0.f;
	float m_slideTimer = 0.f;
	sf::Vector2f m_slideSize = { 75.f,40.f };
	sf::Vector2f m_odlSize = { 75.f,75.f };
	sf::Vector2f m_oldOrigin;
	bool m_onSlide = false;


public:
	//constructeur
	Player(sf::Vector2f position);
	~Player();

	void update();
	void addProj();
	void suppProj();
	bool hadProj();
	void draw(sf::RenderWindow& window);
	void collisionObstacle();
	void throwObject(ObjectManager& manager);
	void slide();
	void timerHandle();
	void handleInput(const sf::Event& event, ObjectManager& manager);
	sf::Vector2f getPosition();
	sf::RectangleShape getShape();

	sf::Vector2f getSpeed();
	sf::Vector2f getMaxSpeed();
	void setSpeed(sf::Vector2f speed);
};
