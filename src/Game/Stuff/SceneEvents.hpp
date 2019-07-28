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

/**
 * @brief       Called when scene becomes current
 */
struct OnEnterScene
{
};

/**
 * @brief       Called when scene stops being current
 */
struct OnLeaveScene
{
};

/**
 * @brief       Called on every window event before Scene::onUpdate
 * @param e     Event from window
 */
struct OnHandleEvent
{
    sf::Event e;
};

}  // namespace game::events
