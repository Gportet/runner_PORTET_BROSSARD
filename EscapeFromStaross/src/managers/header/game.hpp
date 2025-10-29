#pragma once

#include "../../models/header/trashCan.hpp"
#include "../../models/header/Player.hpp"
#include "../../camera/header/camera.hpp"
#include "../../map/header/generator.hpp"
#include "../../models/header/Staross.hpp"
#include "../../managers/header/parallaxManager.hpp"

class Game
{

public:
	sf::RenderWindow window;

	Game();

	void update();

	void event();

	void platformManager();

	void obstacleManager();

	void draw();

	void detectCollisions();
private :
	Map map;
	Generator generator;
	ParallaxManager parallax;
	Camera camera;
	Player p;
	ObjectManager manager;
	Staross s;

};

