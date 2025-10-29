#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

class ParallaxLayer {
public:
    ParallaxLayer(const std::vector<std::string>& paths, float speedFactor, float y);
    void update(float cameraSpeed, float dt);
    void draw(sf::RenderWindow& window, float cameraX);

private:
    std::vector<std::string> m_paths;
    std::vector<std::shared_ptr<sf::Texture>> m_textures;
    std::vector<sf::Sprite> m_spriteCache;

    float m_speedFactor;
    float m_y;
    float m_generationX = 0.f;

    static constexpr float scaleFactor = 2.5f;
    static constexpr int SEGMENT_WIDTH = 512;
    static constexpr int SEGMENT_HEIGHT = 256;
};

