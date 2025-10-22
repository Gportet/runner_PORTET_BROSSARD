#include "Player.h"

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

void Player::update()
{
	collisionObstacle();
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


void Player::throwObject(ObjectManager& manager)
{
	auto c = std::make_unique<Cailloux>(m_position + sf::Vector2f(m_shape.getSize().x / 2, m_shape.getSize().y / 2));
	manager.addCailloux(std::move(c));
}

void Player::slide()
{
	//todo
}

void Player::handleInput(const sf::Event& event, ObjectManager& manager)
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
		case sf::Keyboard::Scan::E:
			throwObject(manager);
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
