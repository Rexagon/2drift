#pragma once

#include <bitset>

#include <SFML/Window/Event.hpp>

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
    void handleEvent(const sf::Event &e);

    bool getKey(sf::Keyboard::Key key) const;
    bool getKeyDown(sf::Keyboard::Key key) const;
    bool getKeyUp(sf::Keyboard::Key key) const;

    bool getMouseButton(sf::Mouse::Button button) const;
    bool getMouseButtonDown(sf::Mouse::Button button) const;
    bool getMouseButtonUp(sf::Mouse::Button button) const;

    sf::Vector2i getMousePosition() const;
    sf::Vector2i getMousePositionDelta() const;

private:
    std::bitset<sf::Keyboard::KeyCount> m_lastKeyboardState{};
    std::bitset<sf::Keyboard::KeyCount> m_currentKeyboardState{};

    std::bitset<sf::Mouse::ButtonCount> m_lastMouseButtonsState{};
    std::bitset<sf::Mouse::ButtonCount> m_currentMouseButtonsState{};

    sf::Vector2i m_lastMousePosition;
    sf::Vector2i m_currentMousePosition;
};

}  // namespace core
