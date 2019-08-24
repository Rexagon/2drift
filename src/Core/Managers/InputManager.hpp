#pragma once

#include <bitset>

#include "Core/Stuff/Event.hpp"
#include "Manager.hpp"

namespace core
{
/**
 * @brief   Input manager
 *
 * Handle events, provide access to current input state
 */
class InputManager final : public Manager
{
public:
    /**
     * @param core  Game core object
     */
    explicit InputManager(Core &core);

    /**
     * @brief       Make last state equal to current
     *
     * Must be called once in the beginning of frame
     */
    void reset();

    /**
     * @brief       Apply event on current input state
     * @param e     Event from window
     */
    void handleEvent(const Event &e);

    bool getKey(uint16_t key) const;
    bool getKeyDown(uint16_t key) const;
    bool getKeyUp(uint16_t key) const;

    bool getMouseButton(uint8_t button) const;
    bool getMouseButtonDown(uint8_t button) const;
    bool getMouseButtonUp(uint8_t button) const;

    const glm::vec2 &getMousePosition() const;
    glm::vec2 getMousePositionDelta() const;

private:
    std::bitset<keyboard::Key::Last> m_lastKeyboardState{};
    std::bitset<keyboard::Key::Last> m_currentKeyboardState{};

    std::bitset<mouse::Button::Last> m_lastMouseButtonsState{};
    std::bitset<mouse::Button::Last> m_currentMouseButtonsState{};

    glm::vec2 m_lastMousePosition{};
    glm::vec2 m_currentMousePosition{};
};

}  // namespace core
