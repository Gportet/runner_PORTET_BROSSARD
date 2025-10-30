#pragma once
#include "../../map/header/map.hpp"

class Generator
{
private:

	float nextGenX = 0;
	const int m_chunkWidth = 1920;
	const int m_platformSpacing = 200;
	const int m_floorY[2] = {600, 300};

public:

	float getNextGenX();
	void generate(std::vector<std::unique_ptr<Obstacle>>&, std::vector<std::unique_ptr<Platform>>&);

};

