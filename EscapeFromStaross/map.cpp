#include "map.h"

bool Map::loadFromFile(const std::string& filename)
{
    std::ifstream file("Assets/Maps/" + filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << filename << std::endl;
        return false;
    }

    std::string line;
    m_mapData.clear();
    while (std::getline(file, line)) {
        m_mapData.push_back(line);
    }

    file.close();
    return true;
}

const std::vector<std::string>& Map::getMapData() const {
    return m_mapData;
}

void Map::print() const {
    for (const auto& line : m_mapData) {
        std::cout << line << std::endl;
    }
}