#include "Player.h"
#include "Cailloux.h"

Player::Player(sf::Vector2f position)
{
	m_shape = sf::RectangleShape(sf::Vector2f(75, 75));
	m_position = position;
	m_speed = sf::Vector2f(50, 0);
	m_shape.setPosition(position);

}

Player::~Player()
{
}

void Player::update(sf::RenderWindow& window)
{
	m_position += (sf::Vector2f(5, 0));
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


void Player::throwObject()
{
	//todo
}

void Player::slide()
{
	//todo
}

void Player::handleInput(const sf::Event& event)
{
	if (auto keyPressed = event.getIf<sf::Event::KeyPressed>() ) {
		switch (keyPressed->scancode)
		{
		case sf::Keyboard::Scan::W:
			m_position -= sf::Vector2f(0, 10);
			break;
		case sf::Keyboard::Scan::S:
			m_position += sf::Vector2f(0, 10);
			break;
		case sf::Keyboard::Scan::D:
			throwObject();
			break;
		case sf::Keyboard::Scan::Space:
			slide();
			break;
		default:
			break;
		}
	}
}

sf::Vector2f Player::getPosition() {
	return m_position;
}