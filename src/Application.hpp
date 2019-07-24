#pragma once

#include <SFML/Window/Event.hpp>

#include "Core/Core.hpp"

namespace app
{
class Application
{
public:
    explicit Application();

    void run();

private:
    void handleEvent(const sf::Event &e);

    Core m_core{};
};

}  // namespace app
