#pragma once

#include <SFML/Window/Event.hpp>

namespace game::events
{
/**
 * @brief       Called right before scene is added to stack
 */
struct OnInitScene
{
};

/**
 * @brief       Called right before scene is removed from stack
 */
struct OnCloseScene
{
};

}  // namespace game::events
