#include "game.h"


Game::Game() : window(sf::VideoMode({ 1920, 1080 }), "Escape from Staross"), camera(window, window.getSize().x, window.getSize().y) , p(sf::Vector2f(300, 800))
{
	window.setFramerateLimit(60);
	generator.generate(map.obstacles, map.platforms);
}



void Game::update()
{
    event();
    if (p.getPosition().x + 800 > generator.getNextGenX()) generator.generate(map.obstacles, map.platforms);
    camera.follow(p.getPosition(), 100);
    window.clear();
    platformManager();
    obstacleManager();
    p.update(window);
    window.display();
}

void Game::event()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
        p.handleInput(event.value());
    }
}

void Game::platformManager()
{
    for (auto it = map.platforms.begin(); it != map.platforms.end(); ) {
        (*it)->draw(window);

        if (p.getPosition().x > (*it)->getPosition().x + 4000) {
            it = map.platforms.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Game::obstacleManager()
{
    for (auto it = map.obstacles.begin(); it != map.obstacles.end(); ) {
        (*it)->draw(window);
        ++it;
    }
}

