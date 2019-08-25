#pragma once

#include <glad/glad.h>
#include <glm/vec3.hpp>

#include "Core/Managers/RenderingManager.hpp"

namespace core
{
class Texture final
{
public:
    /**
     * @brief                   Initialize as 2D texture
     *
     * https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
     *
     * @param core              Game core object
     * @param width             Texture width in pixels
     * @param height            Texture height in pixels
     * @param internalFormat    Number of color components in the texture
     *
     * @param format            Format of the pixel data. Must be one of GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA,
     * GL_BGRA, GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER,
     * GL_STENCIL_INDEX, GL_DEPTH_COMPONENT or GL_DEPTH_STENCIL
     *
     * @param pixelType         Data type of the pixel data. Must be one of GL_UNSIGNED_BYTE, GL_BYTE,
     * GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT and etc.
     *
     * @param                   Data Pointer to the image data in memory
     */
    explicit Texture(Core &core,
                     const glm::uvec2 &size,
                     GLint internalFormat = GL_RGBA8,
                     GLenum format = GL_RGBA,
                     GLenum pixelType = GL_UNSIGNED_BYTE,
                     const void *data = nullptr);

    ~Texture();

    /**
     * @brief           Set this texture as current on specified slot
     * @param slot      Texture slot
     */
    void bind(size_t slot) const;

    /**
     * @brief           Change size of texture
     * @param size      Size in pixels
     */
    void resize(const glm::uvec2 &size);

    /**
     * @brief           Change sampling arithmetic
     *
     * Filter parameters must be one of: GL_NEAREST, GL_LINEAR
     *
     * @param minFilter Filter used for texture minimization
     * @param magFilter Filter used for texture magnification
     */
    void setFilters(GLint minFilter, GLint magFilter);

    /**
     * @brief           Change texture wrapping for all dimensions
     *
     * When this function is called before initialization, it just set parameters locally. When it is called after
     * initialization it will change OpenGL state of this texture.
     *
     * @param wrapMode Component values arithmetic outside [0, 1]. Must be one of: GL_CLAMP_TO_EDGE,
     * GL_CLAMP_TO_BORDER, GL_MIRRORED_REPEAT, GL_REPEAT, or GL_MIRROR_CLAMP_TO_EDGE
     */
    void setWrapMode(GLint wrapMode);

    /**
     * @brief           Change texture wrapping for all dimensions
     *
     * When this function is called before initialization, it just set parameters locally. When it is called after
     * initialization it will change OpenGL state of this texture.
     *
     * @param wrapMode Component values arithmetic outside [0, 1]. Must be one of: GL_CLAMP_TO_EDGE,
     * GL_CLAMP_TO_BORDER, GL_MIRRORED_REPEAT, GL_REPEAT, or GL_MIRROR_CLAMP_TO_EDGE
     * @param component Component number. 0 - width, 1 - height, 2 - depth
     */
    void setWrapMode(GLint wrapMode, size_t component);

    /**
     * @brief Generates LOD textures
     *
     * Must be called only after initialization
     */
    void generateMipmap() const;

    /**
     * @return Texture dimensions. Useless components will be zeroed
     */
    const glm::uvec2 &getSize() const;

    /**
     * @return Native OpenGL handle
     */
    GLuint getHandle() const;

private:
    std::shared_ptr<RenderingManager> m_renderingManager;

    GLuint m_id{0};

    glm::uvec2 m_size;
    GLint m_internalFormat;
    GLenum m_format;
    GLenum m_pixelType;

    GLint m_minFilter{GL_LINEAR};
    GLint m_magFilter{GL_LINEAR};

    GLint m_wrapS{GL_REPEAT};
    GLint m_wrapT{GL_REPEAT};
};

}  // namespace core
