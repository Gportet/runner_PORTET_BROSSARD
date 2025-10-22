#include <iostream>
#include <SFML/Graphics.hpp>

#include "trashCan.h"
#include "Player.h"
#include "camera.h"
#include "map.h"

int main()
{

    TrashCan test(sf::Vector2f(500, 500));

    Map map;
    map.loadFromFile("map.txt");
    map.print();

    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    Camera camera(window, window.getSize().x, window.getSize().y);

    Player p = Player(sf::Vector2f(100, 400));
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
         while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            p.handleInput(event.value());
        }
        camera.follow(p.getPosition(), 100);
        window.clear();
        p.update(window);
        window.display();
    }
}

