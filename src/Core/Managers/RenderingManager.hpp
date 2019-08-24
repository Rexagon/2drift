#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Core/Rendering/Stuff/RenderingParameters.hpp"
#include "WindowManager.hpp"

namespace core
{
/**
 * @brief   Rendering manager
 *
 * Handle OpenGL state and optimizes state calls
 */
class RenderingManager final : public Manager
{
public:
    /**
     * @param core Game core object
     */
    explicit RenderingManager(Core &core);

    /**
     * @brief Force apply current parameters to OpenGL state
     */
    void synchronize();

    /**
     * @brief Apply new parameters
     *
     * Only changed parameters will change OpenGL state
     *
     * @param parameters Parameters pack
     */
    void setRenderingParameters(const RenderingParameters &parameters);

    /**
     * @brief Set depth test status
     * @param enabled Status
     */
    void setDepthTestEnabled(bool enabled);

    /**
     * @brief Check if depth test is enabled
     *
     * Depth test is enabled by default.
     *
     * @return true if enabled
     */
    bool isDepthTestEnabled() const;

    /**
     * @brief Set depth write status
     * @param enabled
     */
    void setDepthWriteEnabled(bool enabled);

    /**
     * @brief Check if depth write is enabled
     *
     * Depth write is enabled by default.
     *
     * @return true if enabled
     */
    bool isDepthWriteEnabled() const;

    /**
     * @brief Set depth test function
     *
     * @param testFunction OpenGL depth test function.
     * Must be one of GL_NEVER, GL_LESS, GL_EQUAL, GL_LEQUAL,
     * GL_GREATER, GL_NOTEQUAL, GL_GEQUAL or GL_ALWAYS
     */
    void setDepthTestFunction(GLenum testFunction);

    /**
     * @brief Get current depth test function
     *
     * GL_LEQUAL is set by default.
     *
     * @return Current depth test function
     */
    GLenum getDepthTestFunction() const;

    /**
     * @brief Set alpha blending status
     * @param enabled Status
     */
    void setBlendingEnabled(bool enabled);

    /**
     * @brief Check if alpha blending is enabled
     *
     * Disabled by default.
     *
     * @return true if enabled
     */
    bool isBlendingEnabled() const;

    /**
     * @brief Specify pixel arithmetic
     *
     * Functions must be one of: GL_ZERO, GL_ONE, GL_SRC_COLOR,
     * GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR,
     * GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA,
     * GL_ONE_MINUS_DST_ALPHA. GL_CONSTANT_COLOR,
     * GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA,
     * and GL_ONE_MINUS_CONSTANT_ALPHA
     *
     * @param src Source function
     * @param dst Destination function
     */
    void setBlendingFunctions(GLenum src, GLenum dst);

    /**
     * @brief Get current alpha blending function for source
     *
     * GL_SRC_ALPHA is set by default.
     *
     * @return Blending function
     */
    GLenum getBlendingFunctionSrc() const;

    /**
     * @brief Get current alpha blending function for destination
     *
     * GL_ONE_MINUS_SRC_ALPHA is set by default.
     *
     * @return Blending function
     */
    GLenum getBlendingFunctionDst() const;

    /**
     * @brief Set face culling status
     * @param enabled Status
     */
    void setFaceCullingEnabled(bool enabled);

    /**
     * @brief Check if face culling is enabled
     *
     * Enabled by default.
     *
     * @return true if enabled
     */
    bool isFaceCullingEnabled() const;

    /**
     * @brief Set face culling side
     * @param side Culled side. Must be one of GL_FRONT, GL_BACK,
     * and GL_FRONT_AND_BACK
     */
    void setFaceCullingSide(GLenum side);

    /**
     * @brief Get face culling side
     *
     * GL_BACK is set by default.
     *
     * @return Side
     */
    GLenum getFaceCullingSide() const;

    /**
     * @brief Set polygon rendering mode
     * @param mode Rendering mode. Must be one of GL_POINT,
     * GL_LINE, and GL_FILL
     */
    void setPolygonMode(GLenum mode);

    /**
     * @brief Get polygon rendering mode
     *
     * GL_FILL is set by default.
     *
     * @return Rendering mode
     */
    GLenum getPolygonMode() const;

    /**
     * @return Current rendering parameters
     */
    const RenderingParameters &getRenderingParameters() const;

    /**
     * @brief Set current viewport parameters
     * @param size Viewport size
     * @param offset Viewport top left offset
     */
    void setViewport(const glm::ivec2 &size, const glm::ivec2 &offset = glm::ivec2());

    /**
     * @brief Set current viewport parameters
     * @param x Viewport left offset
     * @param y Viewport top offset
     * @param width Viewport width
     * @param height Viewport height
     */
    void setViewport(GLint x, GLint y, GLsizei width, GLsizei height);

    /**
     * @return Viewport size
     */
    glm::ivec2 getViewportSize() const;

    /**
     * @return viewport top left offset
     */
    glm::ivec2 getViewportOffset() const;

    /**
     * @param color RGBA, each component is in range [0, 1]
     */
    void setClearColor(const glm::vec4 &color);

    /**
     * @param r Red component in range [0, 1]
     * @param g Green component in range [0, 1]
     * @param b Blue component in range [0, 1]
     * @param a Alpha component in range [0, 1]. 1.0 by default
     */
    void setClearColor(float r, float g, float b, float a = 1.0f);

    /**
     * Opaque black color is set by default.
     *
     * @return Clear color
     */
    glm::vec4 getClearColor() const;

    /**
     * @brief Set clear depth value
     * @param depth Depth value
     */
    void setClearDepth(float depth);

    /**
     * @brief Get clear depth value
     *
     * Default depth value is 1
     *
     * @return Depth value
     */
    float getClearDepth() const;

    /**
     * @brief Set current shader id
     * @param shader Shader id
     */
    void setCurrentShaderId(GLuint shaderId);

    /**
     *  @brief Get current shader id
     */
    GLuint getCurrentShaderId();

    /**
     * @brief Set current frame buffer id
     *
     * Binds frame buffer as GL_FRAMEBUFFER.
     *
     * @param frameBufferId Frame buffer id
     */
    void setCurrentFrameBufferId(GLuint frameBufferId);

    /**
     * @brief Get current frame buffer
     * @return Frame buffer id
     */
    GLuint getCurrentFrameBufferId() const;

    /**
     * @brief Select active texture unit
     * @param slot Unit number. Can be any number, but only
     * first 32 units can be cached by this manager.
     */
    void setActiveTexture(size_t slot);

    /**
     * @brief Bind current texture
     *
     * Active texture will only be changed if pair of target/id is changed
     * for specified unit. To ensure active texture is changed call
     * RenderingManager::setActiveTexture()
     *
     * @param textureTarget Target to which the texture is bound. Must be
     * one of GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D,
     * GL_TEXTURE_1D_ARRAY, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_RECTANGLE,
     * GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BUFFER,
     * GL_TEXTURE_2D_MULTISAMPLE or GL_TEXTURE_2D_MULTISAMPLE_ARRAY
     * @param textureId Texture id
     * @param slot
     */
    void bindTexture(GLenum textureTarget, GLuint textureId, size_t slot);

private:
    static constexpr auto TEXTURE_COUNT = 32u;

    std::shared_ptr<WindowManager> m_windowManager;

    RenderingParameters m_renderingParameters{};

    GLint m_viewport[4]{};
    GLclampf m_clearColor[4]{0.0f, 0.0f, 0.0f, 1.0f};
    float m_clearDepth{1.0f};

    GLuint m_currentShaderId{0};
    GLuint m_currentFrameBufferId{0};

    size_t m_activeTextureUnit{0};
};

}  // namespace core
