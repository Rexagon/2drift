// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "CameraResizingSystem.hpp"

#include "General.hpp"

#include <iostream>

using namespace core;

namespace game
{
CameraResizingSystem::CameraResizingSystem(SharedState &state)
    : System{state}
    , m_windowManager{state.getCore().get<WindowManager>().lock()}
{
    state.getDispatcher().sink<sf::Event>().connect<&CameraResizingSystem::handleEvent>(this);
}


void CameraResizingSystem::update(game::SharedState &state, double /*dt*/)
{
    if (!m_isWindowSizeChanged)
    {
        return;
    }

    std::cout << "Resized" << std::endl;

    auto windowSize = sf::Vector2f(m_windowManager->getWindow().getSize());

    state.getRegistry().view<CameraComponent, WindowResizeableComponent>().each(
        [&windowSize](CameraComponent &cameraComponent, const auto &) {
            cameraComponent.view.setSize(windowSize);
            cameraComponent.view.setCenter(windowSize * 0.5f);
        });

    m_isWindowSizeChanged = false;
}


void CameraResizingSystem::handleEvent(const sf::Event &e)
{
    if (e.type == sf::Event::EventType::Resized)
    {
        m_isWindowSizeChanged = true;
    }
}


}  // namespace game
