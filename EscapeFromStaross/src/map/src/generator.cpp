#include "../header/generator.hpp"


float Generator::getNextGenX()
{
    return nextGenX;
}

void Generator::generate(ObjectManager& objManager, std::vector<std::unique_ptr<Platform>>& platforms)
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
            float oX = rand() % (50, 900);
            sf::Vector2f pos(x + oX, m_floorY[floor] - 100);
            objManager.addObstacle(std::make_unique<TrashCan>(pos));
        }
    }
    float probToSpawnOnFirstFloor = rand() % 2;
    if (probToSpawnOnFirstFloor == 0) objManager.addObstacle(std::make_unique<TrashCan>(sf::Vector2f(nextGenX + 100, 690)));
    nextGenX += m_chunkWidth;
}


