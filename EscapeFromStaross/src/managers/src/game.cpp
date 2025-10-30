#include "../header/game.hpp"


Game::Game() : window(sf::VideoMode({ 1920, 1080 }), "Escape from Staross"), camera(window, window.getSize().x, window.getSize().y), p(sf::Vector2f(300, 800)), manager(ObjectManager(window)), s(Staross(window, camera, p)), floor(800.f, 1920.f, 300.f)
{
	window.setFramerateLimit(60);
	generator.generate(map.obstacles, map.platforms);
}



void Game::update()
{
    float dt = clock.restart().asSeconds();;
    event();
    if (p.getPosition().x + 800 > generator.getNextGenX()) generator.generate(map.obstacles, map.platforms);
    camera.follow(p.getPosition(), 100.f);

    window.clear();

    parallax.draw(window);

    platformManager();
    obstacleManager();
    p.update(map.platforms, floor);
    s.update();
    draw();
    window.display();
	detectCollisions();
}

void Game::event()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
        p.handleInput(event.value(), manager);
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

void Game::draw() {
	floor.draw(window);
    p.draw(window);
    s.draw();
}


void Game::detectCollisions()
{

    for (size_t i = 0; i < map.obstacles.size(); ++i) {
        if ((p.getShape().getGlobalBounds().findIntersection(map.obstacles[i]->getShape().getGlobalBounds()))) {
            map.obstacles.erase(map.obstacles.begin() + i);
            --i;
			p.setSpeed(p.getMaxSpeed() / 5.f);
        }
    }



    sf::FloatRect playerBounds = p.getShape().getGlobalBounds();

    if (playerBounds.position.y + playerBounds.size.y > floor.getY() &&
        p.getSpeed().y > 0.f)
    {
        p.getShape().setPosition(sf::Vector2f(playerBounds.position.x,floor.getY() - playerBounds.size.y));
    }



}



