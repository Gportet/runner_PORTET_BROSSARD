#include <iostream>
#include <SFML/Graphics.hpp>
#include "./managers/header/StateManager.hpp"
#include "./managers/header/game.hpp"

int main()
{
    srand(time(NULL));
    srand(static_cast<unsigned>(time(nullptr)));
    StateManager manager;
    manager.run();
}

