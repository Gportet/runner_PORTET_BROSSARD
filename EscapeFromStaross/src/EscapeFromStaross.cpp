#include <iostream>
#include <SFML/Graphics.hpp>
#include "./managers/header/MenuManager.hpp"
#include "./managers/header/game.hpp"

int main()
{
    srand(time(NULL));
    srand(static_cast<unsigned>(time(nullptr)));
    MenuManager manager;
    manager.run();
}

