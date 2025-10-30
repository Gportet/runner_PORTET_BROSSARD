#include "../header/Player.hpp"

Player::Player(sf::Vector2f position) : m_position(position),m_jumpTexture(), m_fallTexture(),  m_texture(), m_sprite(m_texture)
{
	if (!m_texture.loadFromFile("Assets/Textures/Player/characters/3 Cyborg/Cyborg_run.png")) {
		throw std::runtime_error("Failed to load player texture");
	}
	if (!m_fallTexture.loadFromFile("Assets/Textures/Player/characters/3 Cyborg/Cyborg_jump.png")) {
		throw std::runtime_error("Failed to load player texture");
	}
	if (!m_jumpTexture.loadFromFile("Assets/Textures/Player/characters/3 Cyborg/Cyborg_doublejump.png")) {
		throw std::runtime_error("Failed to load player texture");
	}
	
	m_shape = sf::RectangleShape(sf::Vector2f(75, 75));
	m_speed = sf::Vector2f(5, 0);
	max_speed = sf::Vector2f(10, 0);
	m_shape.setPosition(position);

	m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0),sf::Vector2i( 48, 48)));
	m_sprite.setScale(sf::Vector2f(3.f, 3.f));
	m_sprite.setOrigin(sf::Vector2f(2.f, 24.f));
}

Player::~Player()
{
}

void Player::animate()
{
	int frameNb = 6;

	if (m_verticalSpeed < -1.f) {
		m_sprite.setTexture(m_jumpTexture);
		frameNb = 6;
	}

	else if (m_verticalSpeed > 5.f) {
		m_sprite.setTexture(m_fallTexture);
		frameNb = 4;
	}

	else if (m_verticalSpeed == 0.f && m_isOnGround){
		m_sprite.setTexture(m_texture);
		frameNb = 6;
	}
	float elapsed = animationClock.getElapsedTime().asMilliseconds();
	if (elapsed > 100.f) {
		sf::IntRect rect = m_sprite.getTextureRect();
		rect.position.x += 48;
		if (rect.position.x >= 48 * frameNb) {
			rect.position.x = 0;
		}
		m_sprite.setTextureRect(rect);
		animationClock.restart();
	}
	
}

void Player::update(const std::vector<std::unique_ptr<Platform>>& platforms, Floor& floor)
{
	animate();


	m_verticalSpeed += m_gravity;
	
	if (m_verticalSpeed > 24) m_verticalSpeed = 24;

	

	m_position.y += m_verticalSpeed;

	m_position += m_speed;

	sf::FloatRect playerBounds = m_shape.getGlobalBounds();

	// Collision avec les plateformes, obligé de le mettre ici car doit être fait pendant le déplacement

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

	if (m_position.y + playerBounds.size.y > floor.getY() && m_verticalSpeed > 0.f) {
		m_position.y = floor.getY() - playerBounds.size.y;
		m_verticalSpeed = 0.f;
		m_isOnGround = true;
	}

	timerHandle();

	if (m_speed.x < max_speed.x)
		m_speed.x += 0.1f;

	if (m_dropTimer > 0) {
		m_dropTimer--;
		if (m_dropTimer == 0) {
			m_wantsToDrop = false;
		}
	}

	if (m_dashCooldown > 0) {
		m_dashCooldown--;
		if (m_dashCooldown == 0) {
			m_canDash = true;
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
	m_sprite.setPosition(m_position);
	window.draw(m_sprite);

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


void Player::handleInput(ObjectManager& manager)
 {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		if (m_isOnGround && !m_wantsToDrop) {
			m_verticalSpeed = m_jumpSpeed;
			m_isOnGround = false;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		if (m_position.y < 700) {
			m_wantsToDrop = true;
			m_isOnGround = false;
			m_dropTimer = 10;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
		if (hadProj() && m_projTimer <= 0.f)
		{
			throwObject(manager);
			suppProj();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
		slide();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		if (m_isOnGround && !m_wantsToDrop) {
			m_verticalSpeed = m_jumpSpeed;
			m_isOnGround = false;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		dash();
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

void Player::dash()
{
	if (m_canDash) {
		m_position.x += m_dashDistance;
		m_canDash = false;
		m_dashCooldown = 60;
	}
}
