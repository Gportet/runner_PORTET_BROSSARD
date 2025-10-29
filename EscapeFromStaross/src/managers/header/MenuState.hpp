#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.hpp"


class MenuState : public State
{
private:
	sf::Font font;
	sf::Text playText;
	sf::Text exitText;
	bool startGame = false;
	bool quit = false;
	sf::RectangleShape m_buttonPlay;
	sf::RectangleShape m_buttonQuit;

public:
	MenuState();
	~MenuState();
	void handleInput(const sf::Event& event) override;
	void update() override;
	void render(sf::RenderWindow& window) override;
	bool start() const { return startGame;}
	bool shouldQuit() const { return quit; }
	void handleClick(const sf::Event& event);


};