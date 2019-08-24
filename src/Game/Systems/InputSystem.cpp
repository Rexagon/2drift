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


void InputSystem::update(MainSceneState &state, float dt)
{
    auto &input = state.getInput();

    updateHalfAxis(input.throttleAxis, keyboard::Up, dt, THROTTLE_AXIS_SPEED);
    updateHalfAxis(input.breakAxis, keyboard::Down, dt, THROTTLE_AXIS_SPEED);
    updateHalfAxis(input.clutchAxis, keyboard::Space, dt, THROTTLE_AXIS_SPEED);
    updateHalfAxis(input.handbrakeAxis, keyboard::C, dt, THROTTLE_AXIS_SPEED);

    updateFullAxis(input.steeringAxis, keyboard::Left, keyboard::Right, dt, STEERING_AXIS_SPEED);
}


void InputSystem::updateHalfAxis(float &axis, keyboard::Key key, float dt, float speed, float min, float max)
{
    auto change = 0.0f;
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


void InputSystem::updateFullAxis(float &axis,
                                 keyboard::Key upKey,
                                 keyboard::Key downKey,
                                 float dt,
                                 float speed,
                                 float min,
                                 float max)
{
    auto change = 0.0f;
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
