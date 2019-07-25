#include <iostream>

#include "Game/Game.hpp"

int main()
{
    try
    {
        game::Game application;

        application.run();

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
        return 1;
    }
}
