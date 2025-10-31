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
	sf::Sprite m_sprite;
	sf::RectangleShape m_hitbox;

	// Hitboxes séparées (approximation circulaire pour chaque étoile)
	//std::vector<sf::CircleShape> m_hitboxes;

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
	//sf::Sprite makeStar(sf::Vector2f origin, float radiusCenter, float radius, int points);
	void randomX(float min, float max);
	//void rotate();
	void init();
	void updatePositionDestination();
	void reset();

	sf::Sprite getSprite();
	//std::vector<sf::Sprite> getStars() { return m_sprites; }

	// Accès aux hitboxes (const ref pour éviter copies)
	//const std::vector<sf::CircleShape>& getHitboxes() const { return m_hitboxes; }
};

