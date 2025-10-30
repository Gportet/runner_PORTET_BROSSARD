#include "../header/game.hpp"


Game::Game(sf::RenderWindow& w) : window(w), camera(window, window.getSize().x, window.getSize().y), p(sf::Vector2f(300, 800)), objManager(ObjectManager(window)), s(Staross(window, camera, p)), font(), resumeText(font), exitText(font), floor(800.f, 1920.f, 300.f)
{
	
	generator.generate(objManager, map.platforms);
    initPauseMenu();

}



void Game::update()
{
    float dt = clock.restart().asSeconds();;
    event();
    if (p.getPosition().x + 800 > generator.getNextGenX()) generator.generate(objManager, map.platforms);
    camera.follow(p.getPosition(), 100.f);

    window.clear();

    parallax.draw(window);

    platformManager();
    p.update(map.platforms, floor);
    s.update();
    objManager.update();
    objManager.draw();
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
        if (!isPaused)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                paused();
            }
           p.handleInput(objManager);
        }
        else if(isPaused)
        {
            if (event->is<sf::Event::MouseButtonReleased>())
            {
                const auto& mouse = event->getIf<sf::Event::MouseButtonReleased>();
                const auto& mousePosPI = mouse->position;
                const sf::Vector2f& mousePos = sf::Vector2f(static_cast<float>(mousePosPI.x), static_cast<float>(mousePosPI.y));
                if (mouse->button == sf::Mouse::Button::Left && m_buttonResume.getGlobalBounds().contains(mousePos))
                {
                    paused();
                }
                if (mouse->button == sf::Mouse::Button::Left && m_buttonQuit.getGlobalBounds().contains(mousePos))
                {
                    window.close();
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
            {
                paused();
            }
        }
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


void Game::draw() {
	floor.draw(window);
    p.draw(window);
    s.draw();
}


void Game::detectCollisions()
{
    for (size_t i = 0; i <objManager.getObstacles().size(); ++i) {
        if ((p.getShape().getGlobalBounds().findIntersection(objManager.getObstacles()[i]->getShape().getGlobalBounds()))) {
            objManager.getObstacles().erase(objManager.getObstacles().begin() + i);
            --i;
			p.setSpeed(p.getMaxSpeed() / 5.f);
        }
    }

    sf::FloatRect playerBounds = p.getShape().getGlobalBounds();

    if (playerBounds.position.y + playerBounds.size.y > floor.getY() &&
        p.getSpeed().y > 0.f)
    {
        p.getShape().setPosition(sf::Vector2f(playerBounds.position.x, floor.getY() - playerBounds.size.y));
    }

}


void Game::displayPauseMenu(sf::RenderWindow& window)
{
    adaptMenu();
    event();
    window.clear();
    window.draw(resumeText);
    window.draw(exitText);
    window.draw(m_buttonResume);
    window.draw(m_buttonQuit);
    window.display();
}

void Game::initPauseMenu()
{
    if (!font.openFromFile("Assets/Font/BitcountGridSingle_Roman-Regular.ttf")) {
        // Handle error
    }
    resumeText.setFont(font);
    resumeText.setString("Resume");
    resumeText.setCharacterSize(48);
    resumeText.setFillColor(sf::Color::White);
    resumeText.setPosition(sf::Vector2f(920.f, 400.f));
    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(48);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(sf::Vector2f(920.f, 500.f));

    m_buttonResume = sf::RectangleShape(sf::Vector2f(120, 50));
    m_buttonResume.setFillColor(sf::Color::Transparent);
    m_buttonResume.setPosition(sf::Vector2f(920, 400));

    m_buttonQuit = sf::RectangleShape(sf::Vector2f(120, 50));
    m_buttonQuit.setFillColor(sf::Color::Transparent);
    m_buttonQuit.setPosition(sf::Vector2f(920, 500));
}

void Game::adaptMenu()
{
    sf::View view = camera.getView();
    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();

    float left = center.x - size.x / 2.f;
    sf::Vector2f posButtonResume = sf::Vector2f(left + 920, 400);
    resumeText.setPosition(posButtonResume);
    m_buttonResume.setPosition(posButtonResume);
    sf::Vector2f posButtonQuit = sf::Vector2f(left + 920, 500);
    exitText.setPosition(posButtonQuit);
    m_buttonQuit.setPosition(posButtonQuit);
}



