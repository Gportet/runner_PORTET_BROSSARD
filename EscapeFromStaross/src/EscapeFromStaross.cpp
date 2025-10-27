#include <iostream>
#include <SFML/Graphics.hpp>

#include "./managers/header/game.hpp"

int main()
{
    srand(time(NULL));
    Game game;
    while (game.window.isOpen())
    {
        game.update();
    }
}

