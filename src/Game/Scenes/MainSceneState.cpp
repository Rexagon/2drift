// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "MainSceneState.hpp"

namespace game
{
MainSceneState::MainSceneState(core::Core &core, entt::registry &registry, entt::dispatcher &dispatcher)
    : SharedState(core, registry, dispatcher)
{
}


void MainSceneState::setPlayerCar(entt::entity playerCar)
{
    m_playerCar = playerCar;
}


entt::entity MainSceneState::getPlayerCar() const
{
    return m_playerCar;
}


void MainSceneState::setMainCamera(entt::entity mainCamera)
{
    m_mainCamera = mainCamera;
}


entt::entity MainSceneState::getMainCamera() const
{
    return m_mainCamera;
}

}  // namespace game
