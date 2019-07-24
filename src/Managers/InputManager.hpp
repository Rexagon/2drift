#pragma once

#include <bitset>

#include <SFML/Window/Event.hpp>

#include "Manager.hpp"

namespace app
{
class InputManager : public Manager
{
public:
    explicit InputManager(Core &core);

    void reset();

    void handleEvent(const sf::Event &e);

    bool getKey(sf::Keyboard::Key key) const;
    bool getKeyDown(sf::Keyboard::Key key) const;
    bool getKeyUp(sf::Keyboard::Key key) const;

    bool getMouseButton(sf::Mouse::Button button) const;
    bool getMouseButtonDown(sf::Mouse::Button button) const;
    bool getMouseButtonUp(sf::Mouse::Button button) const;

private:
    std::bitset<sf::Keyboard::KeyCount> m_lastKeyboardState{};
    std::bitset<sf::Keyboard::KeyCount> m_currentKeyboardState{};

    std::bitset<sf::Mouse::ButtonCount> m_lastMouseButtonsState{};
    std::bitset<sf::Mouse::ButtonCount> m_currentMouseButtonsState{};

    sf::Vector2i m_lastMousePosition;
    sf::Vector2i m_currentMousePosition;
};

}  // namespace app
