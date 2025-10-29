#include "../../models/header/parallaxLayer.hpp"

ParallaxLayer::ParallaxLayer(const std::vector<std::string>& paths, float speedFactor, float y)
    : m_paths(paths), m_speedFactor(speedFactor), m_y(y)
{
    if (m_paths.empty()) {
        throw std::runtime_error("No paths provided for ParallaxLayer");
    }

    // Précharger toutes les textures
    m_textures.reserve(m_paths.size());
    for (auto& p : m_paths) {
        sf::Texture tex;
        if (!tex.loadFromFile(p)) {
            std::cerr << "Échec chargement: " << p << std::endl;
        }
        else {
            tex.setRepeated(true);
            m_textures.push_back(std::move(tex));
            std::cout << "OK: " << p
                << " size=" << m_textures.back().getSize().x
                << "x" << m_textures.back().getSize().y
                << std::endl;
        }
    }

    if (m_textures.empty()) {
        throw std::runtime_error("No textures could be loaded for ParallaxLayer");
    }
}

void ParallaxLayer::draw(sf::RenderWindow& window, float cameraX) {
    // Décalage parallax
    float offsetX = cameraX * m_speedFactor;

    int screenWidth = window.getSize().x;

    // Segment de gauche visible basé sur offsetX (et pas cameraX)
    int firstSegment = static_cast<int>(std::floor(offsetX / SEGMENT_WIDTH));

    // Nombre de segments nécessaires pour couvrir l’écran + marge
    int numSegments = screenWidth / SEGMENT_WIDTH + 4; // +2 gauche/droite

    // Décaler un peu pour avoir un tampon à gauche
    firstSegment -= 1;

    for (int i = 0; i < numSegments; ++i) {
        int segIndex = firstSegment + i;

        // Choisir la texture correspondante
        int texIndex = (segIndex % static_cast<int>(m_textures.size()) + m_textures.size())
            % static_cast<int>(m_textures.size());

        sf::Sprite sprite(m_textures[texIndex]);
        sprite.setTextureRect(sf::IntRect{ sf::Vector2i(0, 0) , sf::Vector2i(SEGMENT_WIDTH, SEGMENT_HEIGHT) });

        // Position exacte du segment alignée sur la grille
        float segmentX = segIndex * SEGMENT_WIDTH - offsetX;
        sprite.setPosition(sf::Vector2f(segmentX, m_y));

        window.draw(sprite);
    }
}

