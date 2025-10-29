#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

constexpr int SEGMENT_WIDTH = 576;  // adapte à ton projet
constexpr int SEGMENT_HEIGHT = 324;

class ParallaxLayer {
public:
    ParallaxLayer(const std::vector<std::string>& paths, float speedFactor, float y);

    void draw(sf::RenderWindow& window, float cameraX);

private:
    std::vector<std::string> m_paths;       // chemins des fichiers
    std::vector<sf::Texture> m_textures;    // toutes les textures préchargées

    float m_speedFactor;
    float m_y;
};
