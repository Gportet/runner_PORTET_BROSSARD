#pragma once

#include "trashCan.h"
#include "Player.h"
#include "camera.h"
#include "generator.h"
#include "ObjectManager.h"
#include "Staross.h"
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
private :
	Map map;
	Generator generator;

	Camera camera;
	Player p;
	ObjectManager manager;
	Staross s;

};

