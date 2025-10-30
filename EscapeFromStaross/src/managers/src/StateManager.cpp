#include "../header/StateManager.hpp"

StateManager::StateManager()
{
	window.create(sf::VideoMode({ 1920, 1080 }), "Escape from Staross");
	window.setFramerateLimit(60);
}

void StateManager::run() {
    MenuState menu;
    sf::Clock clock;

    while (window.isOpen()) {
		//si on a besoin d'un delta time
        //float dt = clock.restart().asSeconds();

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            menu.handleInput(*event);
            menu.handleClick(*event);
        }

        if (menu.shouldQuit()) {
            window.close();
            return;
        }

        if (menu.start()) {
            Game game(window); 
            while (window.isOpen()) {
                auto event = window.pollEvent();
                if (!game.menuPause())
                {
                   game.update();
                }
                else
                {
                    game.displayPauseMenu(window);
                }

            }
            break;
        }

        window.clear();
        menu.render(window);
        window.display();
    }
}
