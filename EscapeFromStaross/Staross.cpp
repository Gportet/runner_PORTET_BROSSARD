#include "Staross.h"

Staross::Staross(Player& p, sf::RenderWindow& w) : player(p), window(w)
{
	m_speed = sf::Vector2f(3,0);
    m_posDestination = randomX(300, 1000);
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


float Staross::randomX(float min, float max)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    float r = dist(rng);
    return r;
}

void Staross::rotate()
{
    for (auto& shape : m_shapes)
    {
        shape.rotate(sf::degrees(m_posDestination));
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

void Staross::move()
{
    float xInit = m_shapes[0].getPosition().x;
    float yInit = m_shapes[0].getPosition().x;
    if (xInit >= m_posDestination && m_direction == 1.f || xInit <= m_posDestination && m_direction == -1.f) {
        float xDirection = randomX(300, 1000);
        m_direction = (xInit > xDirection) ? m_direction = -1.f : m_direction = 1.f;
        m_posDestination = xDirection;
    }


    for (auto& shape : m_shapes)
    {
        sf::Vector2f newPos = shape.getPosition() + (m_speed * m_direction) + player.getMaxSpeed();
        shape.setPosition(newPos);
    }
}


