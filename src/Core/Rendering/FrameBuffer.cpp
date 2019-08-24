// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "FrameBuffer.hpp"

#include "Core/Core.hpp"

namespace core
{
FrameBuffer::FrameBuffer(Core &core, const glm::uvec2 &size)
    : m_renderingManager{core.get<RenderingManager>().lock()}
    , m_colorTexture{core, size, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, nullptr}
{
    glGenFramebuffers(1, &m_id);

    m_renderingManager->setCurrentFrameBufferId(m_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorTexture.getHandle(), 0);
}


FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_id);
}


void FrameBuffer::bind()
{
    m_renderingManager->setCurrentFrameBufferId(m_id);
}


void FrameBuffer::resize(const glm::uvec2 &size)
{
    m_colorTexture.resize(size);
}


Texture &FrameBuffer::getColorTexture()
{
    return m_colorTexture;
}


GLuint FrameBuffer::getHandle()
{
    return m_id;
}

}  // namespace core
