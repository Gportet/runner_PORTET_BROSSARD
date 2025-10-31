#pragma once
#include "../../models/header/parallaxLayer.hpp"


class ParallaxManager {
private:
    std::vector<std::unique_ptr<ParallaxLayer>> m_layers;

    static std::vector<std::string> buildPaths(int layerIndex, int numFolders = 8);

public:
    ParallaxManager();

    void update(float cameraSpeed, float dt);

    void draw(sf::RenderWindow& window);
    void reset(sf::RenderWindow& window);
    void init();
};
