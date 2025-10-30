#pragma once
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "MenuState.hpp"

class StateManager
{
private:
	sf::RenderWindow window;
	bool running = true;
public:
	StateManager();
	void run();



};

