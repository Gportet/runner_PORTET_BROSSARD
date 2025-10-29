#pragma once
#include "obstacle.h"
class Wall :
    public Obstacle
{
public:
    Wall(sf::Vector2f position);
};

