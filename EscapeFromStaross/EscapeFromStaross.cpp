#include <iostream>
#include <SFML/Graphics.hpp>

#include "trashCan.h"

int main()
{

    TrashCan test(sf::Vector2f(500, 500));

    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        test.draw(window);
        window.display();
    }
}

