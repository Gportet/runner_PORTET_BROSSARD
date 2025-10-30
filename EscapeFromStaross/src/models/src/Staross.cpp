#include "../header/Staross.hpp"

Staross::Staross(sf::RenderWindow& w, Camera& c, Player& p) : window(w), camera(c), player(p), m_texture()
{
    if (!m_texture.loadFromFile("Assets/Textures/staross.png")) {
        throw std::runtime_error("Failed to load staross texture");
    }
	m_speed = sf::Vector2f(11,0);
    randomX(5, 10);
    updatePositionDestination();
    init();
}

void Staross::init() {

    float yMaxWindow = window.getSize().y;
    float spaceBetween = yMaxWindow / 7;
    sf::Vector2f pos = sf::Vector2f(100, 30);
    for (size_t i = 0; i < 5; i++)
    {
        m_sprites.push_back(makeStar(pos, 40.f, 75.f, 7));
        pos.y += spaceBetween;
    }
    

}

sf::Sprite Staross::makeStar(sf::Vector2f origin, float radiusCenter, float radiusOut, int points )
{
    sf::Sprite star = sf::Sprite(m_texture);

    const float pi = 3.14159265f;
    for (int i = 0; i < points * 2; ++i)
    {
        float angle = i * pi / points - pi / 2; // -pi/2 pour orienter vers le haut
        float radius = (i % 2 == 0) ? radiusCenter : radiusOut;
        sf::Vector2f point(std::cos(angle) * radius, std::sin(angle) * radius);
    }
    // Style
    
    star.setOrigin(star.getLocalBounds().getCenter());

    // Centrer autour de (0,0)
    star.setPosition(origin);
    return star;
}


void Staross::rotate()
{
    for (auto& sprite : m_sprites)
    {
        sprite.rotate(sf::degrees(m_speed.x));
    }
}


void Staross::update() {
    move();
    rotate();
}

void Staross::draw() {

	for (auto& sprite : m_sprites)
	{
		window.draw(sprite);
	}
}

void Staross::randomX(float min, float max)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    float r = dist(rng);
    //permet au aller-retour de ne pas etre trop petit
    abs(m_randomPercentage - r) < 10 ? r += 10*m_direction : r;
    r >= 50 ? r = 50 : r;
    m_randomPercentage = r;
}

void Staross::updatePositionDestination() {
    sf::View view = camera.getView();
    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();

    float left = center.x - size.x / 2.f;

    float pos = left + (m_randomPercentage / 100.f) * size.x;
    m_posDestination = pos;
}

void Staross::move()
{

    updatePositionDestination();
        float xInit = m_sprites[0].getPosition().x;

    if ((m_direction > 0 && xInit >= m_posDestination) ||
        (m_direction < 0 && xInit <= m_posDestination))
    {
        randomX(10, 50);
        updatePositionDestination();
        m_direction = (xInit > m_posDestination) ? -1.f : 1.f;
    }
    for (auto& sprite : m_sprites)
    {
        sf::Vector2f pos = sprite.getPosition();

        m_direction < 0 ? m_speed = sf::Vector2f(2, 0) : m_speed = sf::Vector2f(12,0);
        float step = m_speed.x * m_direction;
        pos.x += step;
        sprite.setPosition(pos);
    }
}


