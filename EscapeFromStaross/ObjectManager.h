#pragma once
#include <iostream>
#include <vector>
#include "Cailloux.h"
#include "obstacle.h"

class ObjectManager
{
private:
	std::vector<std::unique_ptr<Cailloux>> cailloux;
	std::vector<std::unique_ptr<Obstacle>> obstacles;
	sf::RenderWindow& m_window;

public :
	ObjectManager(sf::RenderWindow& window);
	void update();
	void checkCollisions();
	void addCailloux(std::unique_ptr<Cailloux> c);
	void draw();
};

