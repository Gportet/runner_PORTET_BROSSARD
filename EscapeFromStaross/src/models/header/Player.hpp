#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../../models/header/Cailloux.hpp"
#include "../../managers/header/ObjectManager.hpp"
#include "../../models/header/platform.hpp"

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

	float m_dashDistance = 100.f;
	bool m_canDash = true;
	float m_dashCooldown = 1.0f;


public:
	//constructeur
	Player(sf::Vector2f position);
	~Player();

	void update(const std::vector<std::unique_ptr<Platform>>& platforms);
	void addProj();
	void suppProj();
	bool hadProj();
	void draw(sf::RenderWindow& window);
	void throwObject(ObjectManager& manager);
	void slide();
	void timerHandle();
	void handleInput(ObjectManager& manager);
	sf::Vector2f getPosition();
	sf::RectangleShape getShape();

	sf::Vector2f getSpeed();
	sf::Vector2f getMaxSpeed();
	void setSpeed(sf::Vector2f speed);

	void dash();
};
