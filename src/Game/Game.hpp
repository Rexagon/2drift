#pragma once

#include <SFML/Window/Event.hpp>

#include <Core/Core.hpp>

namespace game
{
class Game
{
public:
    explicit Game();

    void run();

private:
    void handleEvent(const sf::Event &e);

    core::Core m_core{};
};

}  // namespace game
