// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Application.hpp"

#include "Managers/InputManager.hpp"
#include "Managers/WindowManager.hpp"

namespace
{
constexpr auto APPLICATION_NAME = "2drift";
}


namespace app
{
Application::Application()
{
    m_core.bind<InputManager>();
    m_core.bind<WindowManager>(sf::Vector2u(1024, 768), APPLICATION_NAME);

    m_core.init();
}


void Application::run()
{
    // Cache managers
    auto inputManager = m_core.get<InputManager>().lock();
    auto windowManager = m_core.get<WindowManager>().lock();

    // Main game loop
    auto &window = windowManager->getWindow();

    sf::Clock timer;

    while (!m_core.isPendingStop())
    {
        const double dt = static_cast<double>(timer.restart().asSeconds());

        // Prepare managers for frame
        inputManager->reset();

        // Handle events
        sf::Event e{};
        while (window.pollEvent(e))
        {
            // Internal handle
            handleEvent(e);

            // Managers handle
            inputManager->handleEvent(e);
        }

        // Display image
        window.display();
    }
}


void Application::handleEvent(const sf::Event &e)
{
    switch (e.type)
    {
        case sf::Event::Closed:
            // Close application after this frame
            m_core.requestExit();
            return;

        default:
            return;
    }
}

}  // namespace app
