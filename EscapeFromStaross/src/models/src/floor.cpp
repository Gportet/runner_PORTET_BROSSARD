#include "../header/floor.hpp"

Floor::Floor(float y, float segmentWidth, float segmentHeight) : m_y(y), m_segmentWidth(segmentWidth), m_segmentHeight(segmentHeight)
{
    if (!m_texture.loadFromFile("Assets/Textures/TileSet/IndustrialPack/1 Tiles/IndustrialTile_59.png")) {
        throw std::runtime_error("Failed to load floor texture");
    }
    m_shape.setTexture(&m_texture);
    m_shape.setSize(sf::Vector2f(m_segmentWidth, m_segmentHeight));
}

void Floor::draw(sf::RenderWindow& window)
{
    // Conversion pixels -> monde
    float worldLeft = window.mapPixelToCoords({ 0,0 }).x;
    float worldRight = window.mapPixelToCoords({ (int)window.getSize().x,0 }).x;
    float pxToWorld = window.mapPixelToCoords({ 1,0 }).x - window.mapPixelToCoords({ 0,0 }).x;

    // Largeur d’un segment en pixels écran
    float Wpx = m_segmentWidth;
    float Wworld = Wpx * pxToWorld;

    // Décalage modulo
    float offset = std::fmod(worldLeft, Wworld);
    if (offset < 0) offset += Wworld;

    // Nombre de segments nécessaires
    int count = (int)((worldRight - worldLeft) / Wworld) + 2;

    for (int i = 0; i < count; ++i) {
        float x = worldLeft - offset + i * Wworld;
        m_shape.setPosition(sf::Vector2f(x, m_y));
        window.draw(m_shape);
    }
}

float Floor::getY() const
{
    return m_y;
}
