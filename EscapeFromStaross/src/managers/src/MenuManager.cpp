#include "../header/MenuManager.hpp"

MenuManager::MenuManager()
{
	window.create(sf::VideoMode({ 1920, 1080 }), "Escape from Staross");
	window.setFramerateLimit(60);
}

void MenuManager::run() {
    MenuState menu;
    sf::Clock clock;

    while (window.isOpen()) {
		//si on a besoin d'un delta time
        //float dt = clock.restart().asSeconds();

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            menu.handleInput(*event);
        }

        if (menu.shouldQuit()) {
            window.close();
            return;
        }

        if (menu.start()) {
            Game game(window); 
            while (window.isOpen()) {
                game.update();
            }
            break;
        }

        window.clear();
        menu.render(window);
        window.display();
    }
}
