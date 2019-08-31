#pragma once

#include <Core/Managers/SceneManager.hpp>
#include <Core/Resources/Stuff/ResourcesScope.hpp>

#include "Game/Stuff/SharedState.hpp"

namespace game
{
class MainSceneState final : public SharedState
{
public:
    explicit MainSceneState(core::Core &core, entt::registry &registry, entt::dispatcher &dispatcher);
};

std::unique_ptr<core::Scene> createMainScene(core::Core &core);

}  // namespace game
