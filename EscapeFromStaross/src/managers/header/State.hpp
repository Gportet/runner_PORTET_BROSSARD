#pragma once
#include <SFML/Graphics.hpp>

class State
{
public:
	virtual ~State() = default;
	virtual void handleInput(const sf::Event& event) =0;
	virtual void update()=0;
	virtual void render(sf::RenderWindow& window)=0;
	virtual bool isFinished() const { return false; }
};
