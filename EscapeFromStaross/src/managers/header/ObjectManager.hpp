#pragma once
#include <iostream>
#include <vector>
#include "../../models/header/Cailloux.hpp"
#include "../../models/header/obstacle.hpp"
#include "../../camera/header/camera.hpp"

class ObjectManager
{
private:
	std::vector<std::unique_ptr<Cailloux>> cailloux;
	std::vector<std::unique_ptr<Obstacle>> obstacles;
	sf::RenderWindow& m_window;
	Camera& m_camera;
public :
	ObjectManager(sf::RenderWindow& window,Camera& camera);
	void update();
	void checkCollisions();
	void addCailloux(std::unique_ptr<Cailloux> c);
	void draw();
};

