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
    m_layers.push_back(std::make_unique<ParallaxLayer>(buildPaths(1), 0.1f, 0.f));  
    m_layers.push_back(std::make_unique<ParallaxLayer>(buildPaths(2), 0.15f, 100.f));
    m_layers.push_back(std::make_unique<ParallaxLayer>(buildPaths(3), 0.3f, 200.f));
    m_layers.push_back(std::make_unique<ParallaxLayer>(buildPaths(4), 0.5f, 400.f));
    m_layers.push_back(std::make_unique<ParallaxLayer>(buildPaths(5), 0.7f, 450.f));
}

void ParallaxManager::update(float cameraSpeed, float dt) {
    for (auto& l : m_layers) {
        l->update(cameraSpeed, dt);
    }
}

void ParallaxManager::draw(sf::RenderWindow& window, float cameraX) {
    for (auto& l : m_layers) {
        l->draw(window, cameraX);
    }
}
