#pragma once

#include <vector>

#include <Core/Managers/SceneManager.hpp>
#include <Core/Resources/ResourcesScope.hpp>

#include "Game/Systems/System.hpp"

namespace game
{
class MainScene final : public core::Scene
{
public:
    explicit MainScene(core::Core &core);

private:
    void onUpdate(double dt) override;

    entt::registry m_registry;

    std::vector<std::unique_ptr<System>> m_systems;

    core::ResourcesScope m_resourcesScope;
};

}  // namespace game
