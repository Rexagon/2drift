#include <iostream>

#include "Application.hpp"

int main()
{
    try
    {
        app::Application application;

        application.run();

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
        return 1;
    }
}
