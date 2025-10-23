#include <iostream>
#include <SFML/Graphics.hpp>

#include "trashCan.h"
#include "Player.h"
#include "camera.h"
#include "generator.h"

int main()
{
    srand(time(NULL));


    TrashCan test(sf::Vector2f(500, 500));

    Map map;
    Generator generator;
    generator.generate(map.obstacles, map.platforms);
    std::cout << map.obstacles.size() << ' ' << map.platforms.size();

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
        if (p.getPosition().x + 800 > generator.getNextGenX()) generator.generate(map.obstacles, map.platforms);
        camera.follow(p.getPosition(), 100);
        window.clear();
        for (auto& platform : map.platforms) {
            platform->draw(window);
        }
        for (auto& obstacle : map.obstacles) {
            obstacle->draw(window);
        }
        p.update(window);
        window.display();
    }
}

