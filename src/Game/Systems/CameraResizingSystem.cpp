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
    state.getDispatcher().sink<Event>().connect<&CameraResizingSystem::handleEvent>(*this);
}


void CameraResizingSystem::update(game::SharedState &state, float /*dt*/)
{
    if (!m_isWindowSizeChanged)
    {
        return;
    }

    auto windowSize = m_windowManager->getSize();

    state.getRegistry().view<CameraComponent, WindowResizeableCameraTag>().each(
        [&windowSize](CameraComponent &camera, const auto &) {
            const auto size = camera.zoom * glm::vec2{windowSize};

            camera.projection = glm::mat3{
                2.0f / size.x, 0.0f,          0.0f,  // row 0
                0.0f,          2.0f / size.y, 0.0f,  // row 1
                0.0f,          0.0f,          1.0f   // row 2
            };
        });

    m_isWindowSizeChanged = false;
}


void CameraResizingSystem::handleEvent(const Event &e)
{
    if (e.type == Event::Type::Resized)
    {
        m_isWindowSizeChanged = true;
    }
}

}  // namespace game
