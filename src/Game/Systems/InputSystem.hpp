#pragma once

#include <Core/Managers/InputManager.hpp>

#include "Game/Scenes/MainScene.hpp"
#include "Game/Stuff/System.hpp"

namespace game
{
class InputSystem final : public System<MainSceneState>
{
public:
    explicit InputSystem(MainSceneState &state);

    void update(MainSceneState &state, double dt) override;

private:
    void updateHalfAxis(
        double &axis, sf::Keyboard::Key key, double dt, double speed, double min = 0.0, double max = 1.0);

    void updateFullAxis(double &axis,
                        sf::Keyboard::Key upKey,
                        sf::Keyboard::Key downKey,
                        double dt,
                        double speed,
                        double min = -1.0,
                        double max = 1.0);

    std::shared_ptr<core::InputManager> m_inputManager;
};

}  // namespace game
