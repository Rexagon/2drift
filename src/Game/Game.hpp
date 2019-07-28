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
    void createScene();

    core::Core m_core{};
};

}  // namespace game
