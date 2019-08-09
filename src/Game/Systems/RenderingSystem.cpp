// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "RenderingSystem.hpp"

#include <entt/entity/helper.hpp>

#include "General.hpp"

using namespace core;

namespace game
{
RenderingSystem::RenderingSystem(SharedState &state)
    : System{state}
    , m_windowManager{state.getCore().get<WindowManager>().lock()}
{
}


void RenderingSystem::update(game::SharedState &state, double dt)
{
    auto &registry = state.getRegistry();
    auto &renderingQueue = state.getRenderingQueue();

    // Prepare window
    auto &window = m_windowManager->getWindow();
    window.clear(sf::Color{36, 32, 32});

    // Find main camera
    auto mainCameraEntities = registry.view<entt::tag<"main_camera"_hs>>();
    if (mainCameraEntities.empty())
    {
        // There is no main camera on scene
        return;
    }
    auto mainCamera = registry.get<CameraComponent>(*mainCameraEntities.begin());

    // Apply view
    window.setView(mainCamera.view);

    // Sort all layers
    renderingQueue.sort();

    // Draw all items on layers
    for (const auto &[key, layer] : renderingQueue.getLayers())
    {
        for (const auto &item : layer)
        {
            window.draw(*item.drawable, item.renderStates);
        }
    }

    // Clear queue
    renderingQueue.clear();
}

}  // namespace game
