#include <iostream>
#include <SFML/Graphics.hpp>

#include "trashCan.h"
#include "Player.h"
#include "camera.h"
#include "ObjectManager.h"
#include "Staross.h"

int main()
{

    TrashCan test(sf::Vector2f(500, 500));


    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Clock clock;
    Camera camera(window, window.getSize().x, window.getSize().y);
    ObjectManager objManager = ObjectManager(window);
    Player p = Player(sf::Vector2f(500, 500));
    Staross s = Staross(p, window);
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
         while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            p.handleInput(event.value(), objManager);
        }
         float deltaTime = clock.getElapsedTime().asSeconds();
        //camera.follow(p.getPosition(), 100);
        window.clear();
        p.update();
        s.update();
        objManager.update();
        p.draw(window);
        s.draw();
        objManager.draw();
        window.display();
    }
}

