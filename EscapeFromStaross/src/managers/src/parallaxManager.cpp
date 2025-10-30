#include "../../managers/header/parallaxManager.hpp"

std::vector<std::string> ParallaxManager::buildPaths(int layerIndex, int numFolders) {
    std::vector<std::string> out;
    for (int folder = 1; folder <= numFolders; ++folder) {
        out.push_back("Assets/Textures/Background/Paralax/background/" +
            std::to_string(folder) + "/Day/" +
            std::to_string(layerIndex) + ".png");
    }
    return out;
}

ParallaxManager::ParallaxManager() {
    m_layers.push_back(std::make_unique<ParallaxLayer>(buildPaths(1), -95.0, 0.f));  
    m_layers.push_back(std::make_unique<ParallaxLayer>(buildPaths(2), -90.0, 50.f));
    m_layers.push_back(std::make_unique<ParallaxLayer>(buildPaths(3), -30, 100.f));
    m_layers.push_back(std::make_unique<ParallaxLayer>(buildPaths(4), 30, 150.f));
    m_layers.push_back(std::make_unique<ParallaxLayer>(buildPaths(5), 100, 120.f));
}

void ParallaxManager::update(float cameraSpeed, float dt) {
    for (auto& l : m_layers) {
        l->update(cameraSpeed, dt);
    }
}

void ParallaxManager::draw(sf::RenderWindow& window) {
    for (auto& l : m_layers) {
        l->draw(window);
    }
}
