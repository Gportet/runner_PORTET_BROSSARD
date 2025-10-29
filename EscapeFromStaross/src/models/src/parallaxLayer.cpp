#include "../../models/header/parallaxLayer.hpp"

ParallaxLayer::ParallaxLayer(const std::vector<std::string>& paths, float speedFactor, float y)
    : m_paths(paths), m_speedFactor(speedFactor), m_y(y)
{
    if (m_paths.empty()) {
        throw std::runtime_error("No paths provided for ParallaxLayer");
    }

    m_textures.reserve(m_paths.size());
    for (const auto& p : m_paths) {
        auto tex = std::make_shared<sf::Texture>();
        if (!tex->loadFromFile(p)) {
            std::cerr << "Échec chargement: " << p << std::endl;
        }
        else {
            tex->setRepeated(true);
            m_textures.push_back(tex);
            std::cout << "OK: " << p
                << " size=" << tex->getSize().x
                << "x" << tex->getSize().y << std::endl;
        }
    }

    for (auto& tex : m_textures) {
        sf::Sprite sprite(*tex);
        sprite.scale(sf::Vector2f(scaleFactor, scaleFactor));
        sprite.setTextureRect({ {0, 0}, {SEGMENT_WIDTH, SEGMENT_HEIGHT} });
        m_spriteCache.push_back(sprite);
    }

    if (m_textures.empty()) {
        throw std::runtime_error("No textures could be loaded for ParallaxLayer");
    }
}

void ParallaxLayer::update(float cameraSpeed, float dt) {
    m_generationX += cameraSpeed * m_speedFactor * dt;
}

void ParallaxLayer::draw(sf::RenderWindow& window, float cameraX) {
    float offsetX = cameraX * m_speedFactor;
    float scaledSegmentWidth = SEGMENT_WIDTH * scaleFactor;
    int screenWidth = window.getSize().x;

    int firstSegment = static_cast<int>(std::floor(m_generationX / scaledSegmentWidth)) - 3;
    int numSegments = screenWidth / static_cast<int>(scaledSegmentWidth) + 10;

    for (int i = 0; i < numSegments; ++i) {
        int segIndex = firstSegment + i;
        float worldX = segIndex * scaledSegmentWidth;
        float screenX = worldX - offsetX;

        if (screenX + scaledSegmentWidth < 0.f || screenX > screenWidth)
            continue;

        int texIndex = (segIndex % m_spriteCache.size() + m_spriteCache.size()) % m_spriteCache.size();
        sf::Sprite& sprite = m_spriteCache[texIndex];
        sprite.setPosition(sf::Vector2f(screenX, m_y));
        window.draw(sprite);
    }
}
