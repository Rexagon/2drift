// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "InputSystem.hpp"

using namespace core;

namespace
{
constexpr auto THROTTLE_AXIS_SPEED = 10.0;
constexpr auto STEERING_AXIS_SPEED = 10.0;

}  // namespace

namespace game
{
InputSystem::InputSystem(MainSceneState &state)
    : System{state}
    , m_inputManager{state.getCore().get<InputManager>().lock()}
{
}


void InputSystem::update(MainSceneState &state, double dt)
{
    auto &input = state.getInput();

    updateHalfAxis(input.throttleAxis, sf::Keyboard::Up, dt, THROTTLE_AXIS_SPEED);
    updateHalfAxis(input.breakAxis, sf::Keyboard::Down, dt, THROTTLE_AXIS_SPEED);
    updateHalfAxis(input.clutchAxis, sf::Keyboard::Space, dt, THROTTLE_AXIS_SPEED);
    updateHalfAxis(input.handbrakeAxis, sf::Keyboard::C, dt, THROTTLE_AXIS_SPEED);

    updateFullAxis(input.steeringAxis, sf::Keyboard::Left, sf::Keyboard::Right, dt, STEERING_AXIS_SPEED);
}


void InputSystem::updateHalfAxis(double &axis, sf::Keyboard::Key key, double dt, double speed, double min, double max)
{
    auto change = 0.0;
    if (m_inputManager->getKey(key))
    {
        change = speed;
    }
    else
    {
        change = -speed;
    }

    axis = std::clamp(axis + change * dt, min, max);
}


void InputSystem::updateFullAxis(
    double &axis, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey, double dt, double speed, double min, double max)
{
    auto change = 0.0;
    if (m_inputManager->getKey(upKey))
    {
        change += speed;
    }
    if (m_inputManager->getKey(downKey))
    {
        change -= speed;
    }

    axis = std::clamp(axis + change * dt, min, max);
}


}  // namespace game
