#include "Player.h"
#include "Cailloux.h"

Player::Player(sf::Vector2f position)
{
	m_shape = sf::RectangleShape(sf::Vector2f(100, 100));
	m_position = position;
	m_speed = sf::Vector2f(50, 0);
	m_shape.setPosition(position);

}

Player::~Player()
{
}

void Player::update(sf::RenderWindow& window)
{

	movement();
	draw(window);
}

void Player::draw(sf::RenderWindow& window)
{ 
	m_shape.setPosition(m_position);
	window.draw(m_shape);
}

void Player::collisionObstacle()
{
	//todo
}

void Player::movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
	{
		m_position -= sf::Vector2f(0, 10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		m_position += sf::Vector2f(0, 10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		slide();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		throwObject();
	}
}

void Player::throwObject()
{
	//todo
}

void Player::slide()
{
	//todo
}

sf::Vector2f Player::getPosition() {
	return m_position;
}