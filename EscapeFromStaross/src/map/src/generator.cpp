#include "../header/generator.hpp"


float Generator::getNextGenX()
{
    return nextGenX;
}

void Generator::generate(std::vector<std::unique_ptr<Obstacle>>& obstacles, std::vector<std::unique_ptr<Platform>>& platforms)
{
    std::vector<int> floorsUsed;
    while (floorsUsed.size() < 2 + rand() % 2) {
        int floor = rand() % (1,2);
        if (std::find(floorsUsed.begin(), floorsUsed.end(), floor) == floorsUsed.end()) {
            floorsUsed.push_back(floor);
        }
    }
    int safeFloor = floorsUsed[rand() % floorsUsed.size()];
    for (int floor : floorsUsed) {
        float x = nextGenX + rand() % (m_chunkWidth);
        platforms.push_back(std::make_unique<Platform>(sf::Vector2f(x, m_floorY[floor])));

        if (floor != safeFloor) {
            sf::Vector2f pos(x + 50, m_floorY[floor] - 100);
            obstacles.push_back(std::make_unique<TrashCan>(pos));
        }
    }
    nextGenX += m_chunkWidth;
}


