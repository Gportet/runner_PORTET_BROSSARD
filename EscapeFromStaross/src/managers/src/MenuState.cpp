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
    playText.setPosition(sf::Vector2f(920.f, 400.f));
    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(48);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(sf::Vector2f(920.f, 500.f));


    m_buttonPlay = sf::RectangleShape(sf::Vector2f(120, 50));
    m_buttonPlay.setFillColor(sf::Color::Transparent);
    m_buttonPlay.setPosition(sf::Vector2f(920, 400));

    m_buttonQuit = sf::RectangleShape(sf::Vector2f(120, 50));
    m_buttonQuit.setFillColor(sf::Color::Transparent);
    m_buttonQuit.setPosition(sf::Vector2f(920, 500));

}



MenuState::~MenuState() = default;

void MenuState::handleInput(const sf::Event& event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        startGame = true;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        quit = true;
}

void MenuState::handleClick(const sf::Event& event)
{
    if (event.is<sf::Event::MouseButtonReleased>())
    {
        const auto& mouse = event.getIf <sf::Event::MouseButtonReleased>();
        const auto& mousePosPI = mouse->position;
        const sf::Vector2f& mousePos = sf::Vector2f(static_cast<float>(mousePosPI.x), static_cast<float>(mousePosPI.y));
        if (mouse->button == sf::Mouse::Button::Left && m_buttonPlay.getGlobalBounds().contains(mousePos))
        {
            startGame = true;
        }
        else if (mouse->button == sf::Mouse::Button::Left && m_buttonQuit.getGlobalBounds().contains(mousePos))
        {
            quit = true;
        }

    }

}

void MenuState::update()  {}

void MenuState::render(sf::RenderWindow& window)  {
	window.draw(playText);
	window.draw(exitText);
    window.draw(m_buttonPlay);
    window.draw(m_buttonQuit);
}


