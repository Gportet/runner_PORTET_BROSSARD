#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "SFML works!");
    Player p = Player(sf::Vector2f(100, 400));
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        p.update(window);
        window.display();
    }
}

