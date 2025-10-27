#include "../header/MenuState.hpp"

MenuState::MenuState()
	: font(), playText(font), exitText(font) // Initialisation correcte des membres, Texte associés à la police
{
    if (!font.openFromFile("Assets/Font/BitcountGridSingle_Roman-Regular.ttf")) {
        // Handle error
    }
    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(48);
    playText.setFillColor(sf::Color::White);
    playText.setPosition(sf::Vector2f(300.f, 200.f));
    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(48);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(sf::Vector2f(300.f, 300.f));
}

MenuState::~MenuState() = default;

void MenuState::handleInput(const sf::Event& event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        startGame = true;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        quit = true;
}


void MenuState::update()  {}

void MenuState::render(sf::RenderWindow& window)  {
	window.draw(playText);
	window.draw(exitText);
}
