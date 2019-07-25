// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "InputManager.hpp"

namespace
{
bool isKeyValid(const sf::Keyboard::Key key)
{
    return static_cast<short>(key) >= 0 && static_cast<short>(key) < sf::Keyboard::KeyCount;
}


bool isMouseButtonValid(const sf::Mouse::Button button)
{
    return static_cast<short>(button) >= 0 && static_cast<short>(button) < sf::Mouse::ButtonCount;
}
}  // namespace


namespace core
{
InputManager::InputManager(Core &core)
    : Manager{core}
{
}


void InputManager::reset()
{
    m_lastKeyboardState = m_currentKeyboardState;
    m_lastMouseButtonsState = m_currentMouseButtonsState;
    m_lastMousePosition = m_currentMousePosition;
}


void InputManager::handleEvent(const sf::Event &e)
{
    switch (e.type)
    {
        case sf::Event::KeyPressed:
            if (auto key = e.key.code; isKeyValid(key))
            {
                m_currentKeyboardState.set(key);
            }
            return;

        case sf::Event::KeyReleased:
            if (auto key = e.key.code; isKeyValid(key))
            {
                m_currentKeyboardState.reset(key);
            }
            return;

        case sf::Event::MouseButtonPressed:
            if (auto button = e.mouseButton.button; isMouseButtonValid(button))
            {
                m_currentMouseButtonsState.set(button);
            }
            return;

        case sf::Event::MouseButtonReleased:
            if (auto button = e.mouseButton.button; isMouseButtonValid(button))
            {
                m_currentMouseButtonsState.reset(button);
            }
            return;

        case sf::Event::MouseMoved:
            m_currentMousePosition = sf::Vector2i{e.mouseMove.x, e.mouseMove.y};
            return;

        default:
            return;
    }
}


bool InputManager::getKey(const sf::Keyboard::Key key) const
{
    return isKeyValid(key) && m_currentKeyboardState[key];
}


bool InputManager::getKeyDown(const sf::Keyboard::Key key) const
{
    return isKeyValid(key) && !m_lastKeyboardState[key] && m_currentKeyboardState[key];
}


bool InputManager::getKeyUp(const sf::Keyboard::Key key) const
{
    return isKeyValid(key) && m_lastKeyboardState[key] && !m_currentKeyboardState[key];
}


bool InputManager::getMouseButton(const sf::Mouse::Button button) const
{
    return isMouseButtonValid(button) && m_currentMouseButtonsState[button];
}


bool InputManager::getMouseButtonDown(const sf::Mouse::Button button) const
{
    return isMouseButtonValid(button) && !m_lastMouseButtonsState[button] && m_currentMouseButtonsState[button];
}


bool InputManager::getMouseButtonUp(const sf::Mouse::Button button) const
{
    return isMouseButtonValid(button) && m_lastMouseButtonsState[button] && !m_currentMouseButtonsState[button];
}

}  // namespace core
