#pragma once

#include <Core/Managers/SceneManager.hpp>
#include <Core/Resources/Stuff/ResourcesScope.hpp>

#include "Game/Stuff/SharedState.hpp"

namespace game
{
class MainSceneState final : public SharedState
{
public:
    struct Input
    {
        float steeringAxis = 0.0f;

        float throttleAxis = 0.0f;
        float breakAxis = 0.0f;
        float clutchAxis = 0.0f;
        float handbrakeAxis = 0.0f;
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
