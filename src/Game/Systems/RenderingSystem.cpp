// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "RenderingSystem.hpp"

using namespace core;

namespace game
{
RenderingSystem::RenderingSystem(SharedState &state)
    : System{state}
    , m_windowManager{state.getCore().get<WindowManager>().lock()}
    , m_renderingManager{state.getCore().get<RenderingManager>().lock()}
    , m_screenBuffer{state.getCore(), m_windowManager->getSize()}
    , m_screenMaterial{state.getCore()}
    , m_screenQuad{}
{
    m_screenBuffer.getColorTexture().setFilters(GL_NEAREST, GL_NEAREST);

    m_renderingManager->setClearColor(0.14f, 0.12f, 0.12f);

    m_screenQuad.update(
        MeshGeometry::createRectangle(glm::vec2{-1.0f, -1.0f}, glm::vec2{1.0f, 1.0f}, MeshGeometry::Position));
}


void RenderingSystem::update(game::SharedState &state, float /*dt*/)
{
    auto &renderingQueue = state.getRenderingQueue();

    const auto &windowSize = m_windowManager->getSize();

    // First pass
    //

    m_screenBuffer.bind();
    m_renderingManager->setViewport(glm::vec2{windowSize} * 0.5f, glm::vec2{windowSize} * 0.25f);

    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Sort all layers
    renderingQueue.sort();

    // Draw all items on layers
    for (const auto &[key, layer] : renderingQueue.getLayers())
    {
        for (const auto &item : layer)
        {
            item.material->bind(*item.materialParameters);
            item.mesh->draw();
        }
    }

    // Clear queue
    renderingQueue.clear();

    // Second pass
    //

    m_renderingManager->setCurrentFrameBufferId(0);
    m_renderingManager->setViewport(windowSize, glm::vec2{});
    m_screenBuffer.getColorTexture().bind(ScreenMaterial::SCREEN_TEXTURE_SLOT);

    m_screenMaterial.bind();
    m_screenQuad.draw();
}

}  // namespace game
