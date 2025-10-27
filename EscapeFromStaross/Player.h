#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Cailloux.h"
#include "ObjectManager.h"
#include "platform.h"

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

	float m_jumpSpeed = -30.f;       
	float m_gravity = 1.f;           
	float m_verticalSpeed = 0.f;  
	bool m_isOnGround = false;      
	bool m_wantsToDrop = false;
	int m_dropTimer = 0;


public:
	//constructeur
	Player(sf::Vector2f position);
	~Player();

	void update(const std::vector<std::unique_ptr<Platform>>& platforms);
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
