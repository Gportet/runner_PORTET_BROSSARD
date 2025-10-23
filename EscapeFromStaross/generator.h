#pragma once
#include "map.h"

class Generator
{
private:

	float nextGenX = 0;
	const int m_chunkWidth = 800;
	const int m_platformSpacing = 200;
	const int m_floorY[3] = { 900, 600, 300 };

public:

	float getNextGenX();
	void generate(std::vector<std::unique_ptr<Obstacle>>&, std::vector<std::unique_ptr<Platform>>&);

};

