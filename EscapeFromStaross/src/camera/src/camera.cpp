#include "../../camera/header/camera.hpp"

Camera::Camera(sf::RenderWindow& window, float width, float height) : view(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(width, height))), window(window) {
    window.setView(view);
}

void Camera::follow(const sf::Vector2f& target, float offsetX) {
    sf::Vector2f current = view.getCenter();
    sf::Vector2f desired = sf::Vector2f(target.x + offsetX, current.y);

    float smoothing = 0.05f;
    sf::Vector2f newCenter = current + (desired - current) * smoothing;

    view.setCenter(newCenter);
    window.setView(view);
}

float Camera::getSpeed() {
    return m_cameraSpeed;
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