#include "Staross.h"

Staross::Staross(Player p) : player(p)
{
	m_speed = sf::Vector2f(20,0);
	m_shapes.push_back(makeStar(sf::Vector2f(-200, -400), 40.f, 75.f, 5));//important en negatif coordonée inversé
    std::cout << "oi";
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
    star.setOrigin(origin);

    return star;
}

//fait varier la vitesse 
void Staross::variationSpeed()
{

}

void Staross::update() {

}

void Staross::draw(sf::RenderWindow& window) {
	for (auto shape : m_shapes)
	{
		window.draw(shape);
	}
}
