#include "parallaxLayer.h"

ParallaxLayer::ParallaxLayer(const std::string& texturePath, float layerSpeed) : speed(layerSpeed), xOffset(0.f), m_sprite(m_texture)
{
	if (!m_texture.loadFromFile(texturePath)) {
		throw std::runtime_error("Failed to load texture");
	}
}
