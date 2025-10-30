#pragma once

#include "../../models/header/trashCan.hpp"
#include "../../models/header/Player.hpp"
#include "../../camera/header/camera.hpp"
#include "../../map/header/generator.hpp"
#include "../../models/header/Staross.hpp"
#include "../../managers/header/parallaxManager.hpp"
#include "../../camera/header/hud.hpp"

class Game
{

public:
	sf::RenderWindow& window;

	Game(sf::RenderWindow& window);

	void update();

	void event();

	void platformManager();

	void draw();

	void detectCollisions();

	void paused() { m_isPaused = !m_isPaused; }
	bool menuPause() { return m_isPaused; }
	void displayPauseMenu(sf::RenderWindow& window);
	void displayGameOverMenu(sf::RenderWindow& window);
	void initPauseMenu();
	void adaptMenu();
	bool gameOver() { return m_gameOver; }
	void play() { m_gameOver = false; }
	void reset();

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
	sf::Text gameOvertext;
	sf::RectangleShape m_buttonResume;
	sf::RectangleShape m_buttonQuit;
	bool m_isPaused = false;
	bool m_gameOver = false;
	Floor floor;
	HUD hud;
};

