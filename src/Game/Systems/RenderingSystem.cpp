// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "RenderingSystem.hpp"

#include <Core/Managers/ResourceManager.hpp>

#include <entt/entity/helper.hpp>

#include "General.hpp"

using namespace core;

namespace game
{
RenderingSystem::RenderingSystem(core::Core &core)
    : System{core}
    , m_windowManager{core.get<WindowManager>().lock()}
    , m_renderingQueue{core.get<ResourceManager>().lock()->get<RenderingQueue>(RENDERING_QUEUE)}
{
}


void RenderingSystem::update(entt::registry &registry, const double dt)
{
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
    m_renderingQueue->sort();

    // Draw all items on layers
    for (const auto &[key, layer] : m_renderingQueue->getLayers())
    {
        for (const auto &item : layer)
        {
            window.draw(*item.drawable, item.renderStates);
        }
    }

    // Clear queue
    m_renderingQueue->clear();
}

}  // namespace game
