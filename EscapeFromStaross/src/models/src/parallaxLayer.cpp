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

	init();
}




void ParallaxLayer::update(float cameraSpeed, float dt) {
    m_generationX += cameraSpeed * m_speedFactor * dt; // pas utilisé pour le moment
}

void ParallaxLayer::init() {
    float W = SEGMENT_WIDTH * scaleFactor;

    float startX = -W * 2;
    for (int i = 0; i < 8; ++i) {

        m_spriteCache[i].setScale(sf::Vector2f(scaleFactor, scaleFactor));
        m_spriteCache[i].setPosition(sf::Vector2f(startX +i * W, m_y));
    }
}
void ParallaxLayer::draw(sf::RenderWindow& window) {
    const float Wpx = SEGMENT_WIDTH * scaleFactor;

    sf::Vector2f world0 = window.mapPixelToCoords(sf::Vector2i(0, 0));
    sf::Vector2f world1 = window.mapPixelToCoords(sf::Vector2i(1, 0));
    float pxToWorld = world1.x - world0.x;

    float worldLeft = world0.x;
    float Wworld = Wpx * pxToWorld;
    float dxWorld = -m_speedFactor * (pxToWorld)/10;


    for (auto& sprite : m_spriteCache) {
        sprite.move(sf::Vector2f(dxWorld, 0.f));
    }

    // 2. Trouver la position la plus à droite (en monde)
    float maxX = -1e9f;
    for (auto& sprite : m_spriteCache) {
        if (sprite.getPosition().x > maxX)
            maxX = sprite.getPosition().x;
    }

    // 3. Replacer uniquement les sprites sortis à gauche de l’écran
    for (auto& sprite : m_spriteCache) {
        if (sprite.getPosition().x + Wworld < worldLeft) {
            sprite.setPosition(sf::Vector2f(maxX + Wworld, m_y));
            maxX = sprite.getPosition().x;
        }
    }

    // 4. Dessiner
    for (auto& sprite : m_spriteCache) {
        window.draw(sprite);
    }
}










