#pragma once
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "MenuState.hpp"

class MenuManager
{
private:
	sf::RenderWindow window;
	bool running = true;
public:
	MenuManager();
	void run();



};

