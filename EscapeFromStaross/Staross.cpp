#include "Staross.h"

Staross::Staross(sf::RenderWindow& w, Camera& c, Player& p) : window(w), camera(c), player(p)
{
	m_speed = sf::Vector2f(11,0);
    randomX(5, 10);
    updatePositionDestination();
    init();
}

void Staross::init() {

    float yMaxWindow = window.getSize().y;
    float spaceBetween = yMaxWindow / 7;
    sf::Vector2f pos = sf::Vector2f(300, 30);
    for (size_t i = 0; i < 7; i++)
    {
        m_shapes.push_back(makeStar(pos, 40.f, 75.f, 7));
        pos.y += spaceBetween;
    }
    

}

//fonction pour créer les staross
sf::ConvexShape Staross::makeStar(sf::Vector2f origin, float radiusCenter, float radiusOut, int points )
{
    sf::ConvexShape star;
    star.setPointCount(points * 2);

    const float pi = 3.14159265f;
    for (int i = 0; i < points * 2; ++i)
    {
        float angle = i * pi / points - pi / 2; // -pi/2 pour orienter vers le haut
        float radius = (i % 2 == 0) ? radiusCenter : radiusOut;
        sf::Vector2f point(std::cos(angle) * radius, std::sin(angle) * radius);
        star.setPoint(i, point);
    }

    // Style
    star.setFillColor(sf::Color(68, 0, 211)); //violet
    star.setOutlineColor(sf::Color::Black);
    star.setOutlineThickness(2.f);

    // Centrer autour de (0,0)
    star.setOrigin(star.getGeometricCenter());
    star.setPosition(origin);
    return star;
}


void Staross::rotate()
{
    for (auto& shape : m_shapes)
    {
        shape.rotate(sf::degrees(m_speed.x));
    }
}


void Staross::update() {
    move();
    rotate();
}

void Staross::draw() {

	for (auto& shape : m_shapes)
	{
		window.draw(shape);
	}
}

void Staross::randomX(float min, float max)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    float r = dist(rng);
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
    std::cout <<m_posDestination<< std::endl;

    updatePositionDestination();
        float xInit = m_shapes[0].getPosition().x;

    std::cout << xInit << " " << m_posDestination << std::endl;

    if ((m_direction > 0 && xInit >= m_posDestination) ||
        (m_direction < 0 && xInit <= m_posDestination))
    {
        randomX(20, 45);
        updatePositionDestination();
        m_direction = (xInit > m_posDestination) ? -1.f : 1.f;
    }


    for (auto& shape : m_shapes)
    {
        sf::Vector2f pos = shape.getPosition();

        m_direction < 0 ? m_speed = sf::Vector2f(0, 0) : m_speed = sf::Vector2f(12,0);
        float step = m_speed.x * m_direction;
        pos.x += step;
        shape.setPosition(pos);
    }
}


