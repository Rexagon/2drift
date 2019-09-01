// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "InputManager.hpp"

namespace
{
bool isKeyValid(const uint16_t key)
{
    return static_cast<short>(key) <= core::keyboard::Last;
}


bool isMouseButtonValid(const uint8_t button)
{
    return static_cast<short>(button) <= core::mouse::Button::Last;
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


void InputManager::handleEvent(const Event &e)
{
    switch (e.type)
    {
        case Event::Type::KeyPressed:
            if (auto key = e.key.key; isKeyValid(key))
            {
                m_currentKeyboardState.set(static_cast<size_t>(key));
            }
            return;

        case Event::Type::KeyReleased:
            if (auto key = e.key.key; isKeyValid(key))
            {
                m_currentKeyboardState.reset(static_cast<size_t>(key));
            }
            return;

        case Event::Type::MouseButtonPressed:
            if (auto button = e.mouseButton.button; isMouseButtonValid(button))
            {
                m_currentMouseButtonsState.set(button);
            }
            return;

        case Event::Type::MouseButtonReleased:
            if (auto button = e.mouseButton.button; isMouseButtonValid(button))
            {
                m_currentMouseButtonsState.reset(button);
            }
            return;

        case Event::Type::MouseMoved:
            m_currentMousePosition = e.mouseMove.position;
            return;

        default:
            return;
    }
}


bool InputManager::getKey(const uint16_t key) const
{
    return isKeyValid(key) && m_currentKeyboardState[key];
}


bool InputManager::getKeyDown(const uint16_t key) const
{
    return isKeyValid(key) && !m_lastKeyboardState[key] && m_currentKeyboardState[key];
}


bool InputManager::getKeyUp(const uint16_t key) const
{
    return isKeyValid(key) && m_lastKeyboardState[key] && !m_currentKeyboardState[key];
}


bool InputManager::getMouseButton(const uint8_t button) const
{
    return isMouseButtonValid(button) && m_currentMouseButtonsState[button];
}


bool InputManager::getMouseButtonDown(const uint8_t button) const
{
    return isMouseButtonValid(button) && !m_lastMouseButtonsState[button] && m_currentMouseButtonsState[button];
}


bool InputManager::getMouseButtonUp(const uint8_t button) const
{
    return isMouseButtonValid(button) && m_lastMouseButtonsState[button] && !m_currentMouseButtonsState[button];
}


const glm::vec2 &InputManager::getMousePosition() const
{
    return m_currentMousePosition;
}


glm::vec2 InputManager::getMousePositionDelta() const
{
    return m_currentMousePosition - m_lastMousePosition;
}

}  // namespace core
