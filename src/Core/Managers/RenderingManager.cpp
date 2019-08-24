// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "RenderingManager.hpp"

#include <cstring>

#include <glm/gtc/epsilon.hpp>

#include "Core/Core.hpp"

namespace
{
void setEnabled(const GLenum prop, const bool enabled)
{
    if (enabled)
    {
        glEnable(prop);
    }
    else
    {
        glDisable(prop);
    }
}

}  // namespace

namespace core
{
RenderingManager::RenderingManager(Core &core)
    : Manager{core}
    , m_windowManager{core.get<WindowManager>().lock()}
{
}


void RenderingManager::synchronize()
{
    // depth test
    setEnabled(GL_DEPTH_TEST, m_renderingParameters.isDepthTestEnabled);

    // depth write
    glDepthMask(static_cast<GLboolean>(m_renderingParameters.isDepthWriteEnabled));

    // depth test function
    glDepthFunc(m_renderingParameters.depthTestFunction);

    // set blending enabled
    setEnabled(GL_BLEND, m_renderingParameters.isBlendingEnabled);

    // set blending functions
    glBlendFunc(m_renderingParameters.blendingFunctionSrc, m_renderingParameters.blendingFunctionDst);

    // set face culling enabled
    setEnabled(GL_CULL_FACE, m_renderingParameters.isFaceCullingEnabled);

    // set face culling side
    glCullFace(m_renderingParameters.faceCullingSide);

    // set polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, m_renderingParameters.polygonMode);

    // viewport
    glViewport(m_viewport[0], m_viewport[1], m_viewport[2], m_viewport[3]);

    // clear color
    glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);

    // clear depth
    glClearDepth(m_clearDepth);

    // set current shader
    glUseProgram(m_currentShaderId);

    // set current frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, m_currentFrameBufferId);

    // set active texture unit
    glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(m_activeTextureUnit));
}


void RenderingManager::setRenderingParameters(const RenderingParameters &parameters)
{
    setDepthTestEnabled(parameters.isDepthTestEnabled);
    setDepthWriteEnabled(parameters.isDepthWriteEnabled);
    setDepthTestFunction(parameters.depthTestFunction);
    setBlendingEnabled(parameters.isBlendingEnabled);
    setBlendingFunctions(parameters.blendingFunctionSrc, parameters.blendingFunctionDst);
    setFaceCullingEnabled(parameters.isFaceCullingEnabled);
    setFaceCullingSide(parameters.faceCullingSide);
    setPolygonMode(parameters.polygonMode);
}


void RenderingManager::setDepthTestEnabled(const bool enabled)
{
    if (m_renderingParameters.isDepthTestEnabled != enabled)
    {
        m_renderingParameters.isDepthTestEnabled = enabled;
        setEnabled(GL_DEPTH_TEST, enabled);
    }
}


bool RenderingManager::isDepthTestEnabled() const
{
    return m_renderingParameters.isDepthTestEnabled;
}


void RenderingManager::setDepthWriteEnabled(const bool enabled)
{
    if (m_renderingParameters.isDepthWriteEnabled != enabled)
    {
        m_renderingParameters.isDepthWriteEnabled = enabled;
        glDepthMask(static_cast<GLboolean>(enabled));
    }
}


bool RenderingManager::isDepthWriteEnabled() const
{
    return m_renderingParameters.isDepthWriteEnabled;
}


void RenderingManager::setDepthTestFunction(const GLenum testFunction)
{
    if (m_renderingParameters.depthTestFunction != testFunction)
    {
        m_renderingParameters.depthTestFunction = testFunction;
        glDepthFunc(testFunction);
    }
}


GLenum RenderingManager::getDepthTestFunction() const
{
    return m_renderingParameters.depthTestFunction;
}


void RenderingManager::setBlendingEnabled(const bool enabled)
{
    if (m_renderingParameters.isBlendingEnabled != enabled)
    {
        m_renderingParameters.isBlendingEnabled = enabled;
        setEnabled(GL_BLEND, enabled);
    }
}


bool RenderingManager::isBlendingEnabled() const
{
    return m_renderingParameters.isBlendingEnabled;
}


void RenderingManager::setBlendingFunctions(const GLenum src, const GLenum dst)
{
    if (m_renderingParameters.blendingFunctionSrc != src || m_renderingParameters.blendingFunctionDst != dst)
    {
        m_renderingParameters.blendingFunctionSrc = src;
        m_renderingParameters.blendingFunctionDst = dst;
        glBlendFunc(src, dst);
    }
}


GLenum RenderingManager::getBlendingFunctionSrc() const
{
    return m_renderingParameters.blendingFunctionSrc;
}


GLenum RenderingManager::getBlendingFunctionDst() const
{
    return m_renderingParameters.blendingFunctionDst;
}


void RenderingManager::setFaceCullingEnabled(const bool enabled)
{
    if (m_renderingParameters.isFaceCullingEnabled != enabled)
    {
        m_renderingParameters.isFaceCullingEnabled = enabled;
        setEnabled(GL_CULL_FACE, enabled);
    }
}


bool RenderingManager::isFaceCullingEnabled() const
{
    return m_renderingParameters.isFaceCullingEnabled;
}


void RenderingManager::setFaceCullingSide(const GLenum side)
{
    if (m_renderingParameters.faceCullingSide != side)
    {
        m_renderingParameters.faceCullingSide = side;
        glCullFace(side);
    }
}


GLenum RenderingManager::getFaceCullingSide() const
{
    return m_renderingParameters.faceCullingSide;
}


void RenderingManager::setPolygonMode(const GLenum mode)
{
    if (m_renderingParameters.polygonMode != mode)
    {
        m_renderingParameters.polygonMode = mode;
        glPolygonMode(GL_FRONT_AND_BACK, mode);
    }
}


GLenum RenderingManager::getPolygonMode() const
{
    return m_renderingParameters.polygonMode;
}


const RenderingParameters &RenderingManager::getRenderingParameters() const
{
    return m_renderingParameters;
}


void RenderingManager::setViewport(const glm::ivec2 &size, const glm::ivec2 &offset)
{
    setViewport(offset.x, offset.y, size.x, size.y);
}


void RenderingManager::setViewport(const GLint x, const GLint y, const GLsizei width, const GLsizei height)
{
    if (m_viewport[0] != x || m_viewport[1] != y || m_viewport[2] != width || m_viewport[3] != height)
    {
        m_viewport[0] = x;
        m_viewport[1] = y;
        m_viewport[2] = width;
        m_viewport[3] = height;
        glViewport(x, y, width, height);
    }
}


glm::ivec2 RenderingManager::getViewportSize() const
{
    return glm::ivec2(m_viewport[2], m_viewport[3]);
}


glm::ivec2 RenderingManager::getViewportOffset() const
{
    return glm::ivec2(m_viewport[0], m_viewport[1]);
}


void RenderingManager::setClearColor(const glm::vec4 &color)
{
    if (!std::memcmp(&color[0], &m_clearColor[0], sizeof(GLclampf) * 4))
    {
        std::memcpy(&m_clearColor[0], &color[0], sizeof(GLclampf) * 4);

        glClearColor(color.r, color.g, color.b, color.a);
    }
}


void RenderingManager::setClearColor(const float r, const float g, const float b, const float a)
{
    if (glm::epsilonNotEqual(m_clearColor[0], r, 0.0f) || glm::epsilonNotEqual(m_clearColor[1], g, 0.0f) ||
        glm::epsilonNotEqual(m_clearColor[2], b, 0.0f) || glm::epsilonNotEqual(m_clearColor[3], a, 0.0f))
    {
        m_clearColor[0] = r;
        m_clearColor[1] = g;
        m_clearColor[2] = b;
        m_clearColor[3] = a;

        glClearColor(r, g, b, a);
    }
}


glm::vec4 RenderingManager::getClearColor() const
{
    return glm::vec4(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
}


void RenderingManager::setClearDepth(const float depth)
{
    if (glm::epsilonNotEqual(m_clearDepth, depth, 0.0f))
    {
        m_clearDepth = depth;
        glClearDepth(depth);
    }
}


float RenderingManager::getClearDepth() const
{
    return m_clearDepth;
}


void RenderingManager::setCurrentShaderId(GLuint shaderId)
{
    if (m_currentShaderId != shaderId)
    {
        m_currentShaderId = shaderId;
        glUseProgram(shaderId);
    }
}


GLuint RenderingManager::getCurrentShaderId()
{
    return m_currentShaderId;
}


void RenderingManager::setCurrentFrameBufferId(const GLuint frameBufferId)
{
    if (m_currentFrameBufferId != frameBufferId)
    {
        m_currentFrameBufferId = frameBufferId;
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
    }
}


GLuint RenderingManager::getCurrentFrameBufferId() const
{
    return m_currentFrameBufferId;
}


void RenderingManager::setActiveTexture(const size_t slot)
{
    if (slot != m_activeTextureUnit)
    {
        m_activeTextureUnit = slot;
        glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(slot));
    }
}


void RenderingManager::bindTexture(const GLenum textureTarget, const GLuint textureId, const size_t slot)
{
    setActiveTexture(slot);

    // TODO: find way to properly cache textures

    glBindTexture(textureTarget, textureId);
}

}  // namespace core
