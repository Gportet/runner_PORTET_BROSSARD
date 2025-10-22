#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Map
{
private:

	std::vector<std::string> mapData;

public:

	bool loadFromFile(const std::string& filename);
	const std::vector<std::string>& getMapData() const;
	void print() const;
};

