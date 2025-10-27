#include "Player.h"

Player::Player(sf::Vector2f position)
{
	m_shape = sf::RectangleShape(sf::Vector2f(75, 75));
	m_position = position;
	m_speed = sf::Vector2f(5, 0);
	max_speed = sf::Vector2f(10, 0);
	m_shape.setPosition(position);

}

Player::~Player()
{
}

void Player::update(const std::vector<std::unique_ptr<Platform>>& platforms)
{
	m_verticalSpeed += m_gravity;
	
	if (m_verticalSpeed > 24) m_verticalSpeed = 24;

	m_position.y += m_verticalSpeed;

	m_position += m_speed;

	m_isOnGround = false;
	sf::FloatRect playerBounds = m_shape.getGlobalBounds();

	for (auto& platform : platforms) {

		sf::FloatRect platformBounds = platform->getShape().getGlobalBounds();

		float playerBottom = playerBounds.position.y + playerBounds.size.y;
		float platformTop = platformBounds.position.y;

		if (playerBounds.findIntersection(platformBounds) && m_verticalSpeed > 0 && playerBottom - 25 < platformTop && !m_wantsToDrop) {

			m_position.y = platformTop - playerBounds.size.y;
			m_verticalSpeed = 0.f;
			m_isOnGround = true;
		}
	}

	collisionObstacle();
	timerHandle();

	if (m_speed.x < max_speed.x)
		m_speed.x += 0.1f;

	if (m_dropTimer > 0) {
		m_dropTimer--;
		if (m_dropTimer == 0) {
			m_wantsToDrop = false;
		}
	}

}


void Player::addProj()
{
	m_projectiles += 1;
}

void Player::suppProj()
{
	m_projectiles >= 0 ? m_projectiles -= 1 : m_projectiles = 0;
}

bool Player::hadProj()
{
	return m_projectiles > 0;
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
	m_projTimer = 20.f;
}

void Player::slide()
{
	if (m_slideTimer <= 0.f) {
		m_oldOrigin = m_shape.getOrigin();
		float bottomY = m_position.y + m_shape.getSize().y;
		m_position.y = bottomY - m_slideSize.y;
		m_shape.setSize(m_slideSize);
		m_shape.setPosition(m_position);
		m_slideTimer = 30.f;
		m_onSlide = true;
	}
}

void Player::timerHandle()
{
	m_slideTimer -= 1.f;
	m_projTimer -= 1.f;

	if (m_slideTimer <= 0.f && m_onSlide)
	{
		float bottomY = m_position.y + m_shape.getSize().y;
		m_shape.setOrigin(m_oldOrigin);
		m_shape.setSize(m_odlSize); 
		m_position.y = bottomY - m_odlSize.y; 
		m_shape.setPosition(m_position);

		m_onSlide = false;
	}
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
			m_wantsToDrop = true;
			m_dropTimer = 10;
			break;
		case sf::Keyboard::Scan::E:
			if (hadProj() && m_projTimer <= 0.f)
			{
				throwObject(manager);
				suppProj();
			}
			break;
		case sf::Keyboard::Scan::LControl:
			slide();
			break;
		case sf::Keyboard::Scan::Space:
			if (m_isOnGround && !m_wantsToDrop) {
				m_verticalSpeed = m_jumpSpeed;
				m_isOnGround = false;
			}
			break;
		default:
			break;
		}
	}
}

sf::Vector2f Player::getPosition() {
	return m_position;
}

sf::RectangleShape Player::getShape() {
	return m_shape;
}

sf::Vector2f Player::getSpeed()
{
	return m_speed;
}

sf::Vector2f Player::getMaxSpeed() {
	return max_speed;
}

void Player::setSpeed(sf::Vector2f speed)
{
	m_speed = speed;
}
