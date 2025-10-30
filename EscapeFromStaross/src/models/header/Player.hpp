#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../../models/header/Cailloux.hpp"
#include "../../managers/header/ObjectManager.hpp"
#include "../../models/header/platform.hpp"
#include "../../models/header/floor.hpp"


class Player
{
private:


	sf::RectangleShape m_shape;
	sf::Texture m_jumpTexture;
	sf::Texture m_fallTexture;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_speed;
	sf::Vector2f max_speed;
	sf::Vector2f m_position;
	int m_projectiles = 50;
	float m_projTimer = 0.f;
	sf::Vector2f m_oldOrigin;
	float m_jumpSpeed = -25.f;       
	float m_gravity = 1.f;           
	float m_verticalSpeed = 0.f;  
	bool m_isOnGround = false;      
	bool m_wantsToDrop = false;
	int m_dropTimer = 0;

	float m_dashDistance = 100.f;
	bool m_canDash = true;
	float m_dashCooldown = 1.0f;

	sf::Clock animationClock;
public:
	//constructeur
	Player(sf::Vector2f position);
	~Player();


	void animate();
	void update(const std::vector<std::unique_ptr<Platform>>& platforms, Floor& floor);
	void addProj();
	void suppProj();
	bool hadProj();
	void draw(sf::RenderWindow& window);
	void throwObject(ObjectManager& manager);
	void handleInput(ObjectManager& manager);
	void setPos(sf::Vector2f pos) { m_position = pos; }
	sf::Vector2f getPosition();
	sf::RectangleShape getShape();

	sf::Vector2f getSpeed();
	sf::Vector2f getMaxSpeed();
	void setSpeed(sf::Vector2f speed);

	void dash();

	// Réinitialise l'état interne du joueur (vitesse, timers, flags)
	void reset();
};
