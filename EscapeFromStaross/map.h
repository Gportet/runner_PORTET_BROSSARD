#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "trashCan.h"
#include "platform.h"

class Map
{
private:

	std::vector<std::string> m_mapData;


public:

	bool loadFromFile(const std::string& filename);
	const std::vector<std::string>& getMapData() const;
	void print() const;



	std::vector<std::unique_ptr<Obstacle>> obstacles;
	std::vector<std::unique_ptr<Platform>> platforms;

};

