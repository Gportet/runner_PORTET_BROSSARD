#include <iostream>
#include <SFML/Graphics.hpp>

#include "game.h"

int main()
{
    srand(time(NULL));
    Game game;
    while (game.window.isOpen())
    {
        game.update();
    }
}

