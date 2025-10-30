#pragma once
#include "../header/obstacle.hpp"
class Wall :
    public Obstacle
{
public:
    Wall(sf::Vector2f position);
};

