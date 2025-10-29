#pragma once
#include <SFML/Graphics.hpp>
#include "../../models/header/trashCan.hpp"
#include "../../models/header/Player.hpp"
#include "../../camera/header/camera.hpp"
#include "../../map/header/generator.hpp"
#include "../../models/header/Staross.hpp"
#include "../../managers/header/parallaxManager.hpp"

class Game
{

public:
	sf::RenderWindow& window;

	Game(sf::RenderWindow& window);

	void update();

	void event();

	void platformManager();

	void obstacleManager();

	void draw();

	void detectCollisions();

	void paused() { isPaused = !isPaused; }
	bool menuPause() { return isPaused; }
	void displayPauseMenu(sf::RenderWindow& window);
	void initPauseMenu();
	void adaptMenu();

private :
	sf::Clock clock;

	Map map;
	Generator generator;
	ParallaxManager parallax;
	Camera camera;
	Player p;
	ObjectManager objManager;
	Staross s;


	sf::Font font;
	sf::Text resumeText;
	sf::Text exitText;
	sf::RectangleShape m_buttonResume;
	sf::RectangleShape m_buttonQuit;
	bool isPaused = false;

};

