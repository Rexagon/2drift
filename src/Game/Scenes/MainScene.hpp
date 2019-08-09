#pragma once

#include <Core/Managers/SceneManager.hpp>

#include "Game/Stuff/SharedState.hpp"

namespace game
{
class MainSceneState final : public SharedState
{
public:
    struct Input
    {
        double steeringAxis = 0.0;

        double throttleAxis = 0.0;
        double breakAxis = 0.0;
        double clutchAxis = 0.0;
        double handbrakeAxis = 0.0;
    };

    explicit MainSceneState(core::Core &core, entt::registry &registry, entt::dispatcher &dispatcher);

    inline Input &getInput();

private:
    Input m_input{};
};


inline MainSceneState::Input &MainSceneState::getInput()
{
    return m_input;
}


std::unique_ptr<core::Scene> createMainScene(core::Core &core);

}  // namespace game
