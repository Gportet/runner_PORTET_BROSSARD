#pragma once
#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera(sf::RenderWindow& window, float width, float height);

    void follow(const sf::Vector2f& target, float offsetX);

    void setZoom(float factor);

    void setCenter(const sf::Vector2f& center);

    const sf::View& getView();
private:
    sf::View view;
    sf::RenderWindow& window;
};

