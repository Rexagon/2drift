// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "PlayerCarControlSystem.hpp"

#include "Game/Components/Car.hpp"
#include "Game/Components/General.hpp"

using namespace core;

namespace
{
constexpr auto THROTTLE_AXIS_SPEED = 10.0;
constexpr auto STEERING_AXIS_SPEED = 10.0;

}  // namespace

namespace game
{
PlayerCarControlSystem::PlayerCarControlSystem(MainSceneState &state)
    : System{state}
    , m_inputManager{state.getCore().get<InputManager>().lock()}
{
}


void PlayerCarControlSystem::update(MainSceneState &state, float dt)
{
    auto &registry = state.getRegistry();

    registry.view<CarControlsComponent, PlayerControllableTag>().each(
        [this, &dt](CarControlsComponent &controls, const PlayerControllableTag &) {
            updateFullAxis(controls.steering, keyboard::Left, keyboard::Right, dt, STEERING_AXIS_SPEED);

            updateHalfAxis(controls.throttle, keyboard::Up, dt, THROTTLE_AXIS_SPEED);
            updateHalfAxis(controls.breaks, keyboard::Down, dt, THROTTLE_AXIS_SPEED);
            updateHalfAxis(controls.clutch, keyboard::Space, dt, THROTTLE_AXIS_SPEED);
            updateHalfAxis(controls.handbrake, keyboard::C, dt, THROTTLE_AXIS_SPEED);
        });
}


void PlayerCarControlSystem::updateHalfAxis(float &axis, keyboard::Key key, float dt, float speed, float min, float max)
{
    float change;
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


void PlayerCarControlSystem::updateFullAxis(float &axis,
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
