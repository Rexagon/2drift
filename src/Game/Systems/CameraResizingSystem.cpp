// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "CameraResizingSystem.hpp"

#include "General.hpp"

using namespace core;

namespace game
{
CameraResizingSystem::CameraResizingSystem(SharedState &state)
    : System{state}
    , m_windowManager{state.getCore().get<WindowManager>().lock()}
{
}


void CameraResizingSystem::operator()(game::SharedState &state, double dt)
{
    auto windowSize = sf::Vector2f(m_windowManager->getWindow().getSize());

    state.getRegistry().view<CameraComponent, WindowResizeableComponent>().each(
        [&windowSize](CameraComponent &cameraComponent, const auto &) {
            cameraComponent.view.setSize(windowSize);
            cameraComponent.view.setCenter(windowSize * 0.5f);
        });
}

}  // namespace game
