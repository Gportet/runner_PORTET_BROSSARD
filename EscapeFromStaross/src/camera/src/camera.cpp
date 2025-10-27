#include "../../camera/header/camera.hpp"

Camera::Camera(sf::RenderWindow& window, float width, float height) : view(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(width, height))), window(window) {
    window.setView(view);
}

void Camera::follow(const sf::Vector2f& target, float offsetX = 100.f) {
    view.setCenter(sf::Vector2f(target.x + offsetX, view.getCenter().y));
    window.setView(view);
}

void Camera::setZoom(float factor) {
    view.zoom(factor);
    window.setView(view);
}

void Camera::setCenter(const sf::Vector2f& center) {
    view.setCenter(center);
    window.setView(view);
}

const sf::View& Camera::getView() {
    return view;
}