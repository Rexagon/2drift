#pragma once

#include "Game/Stuff/SharedState.hpp"

namespace game
{
class MainSceneState final : public SharedState
{
public:
    explicit MainSceneState(core::Core &core, entt::registry &registry, entt::dispatcher &dispatcher);

    void setPlayerCar(entt::entity playerCar);
    entt::entity getPlayerCar() const;

    void setMainCamera(entt::entity mainCamera);
    entt::entity getMainCamera() const;

private:
    entt::entity m_playerCar{};
    entt::entity m_mainCamera{};
};

}  // namespace game
