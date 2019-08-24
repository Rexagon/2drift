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
     * @brief                   Initialize as 1D texture
     *
     * https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage1D.xhtml
     *
     * @param core              Game core object
     * @param width             Texture width in pixels
     * @param internalFormat    Number of color components in the texture
     *
     * @param format            Format of the pixel data. Must be one of GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA,
     * GL_BGRA, GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER,
     * GL_STENCIL_INDEX, GL_DEPTH_COMPONENT or GL_DEPTH_STENCIL
     *
     * @param type              Data type of the pixel data. Must be one of GL_UNSIGNED_BYTE, GL_BYTE,
     * GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT and etc.
     *
     * @param                   Data Pointer to the image data in memory
     */
    explicit Texture(Core &core,
                     unsigned int width,
                     GLint internalFormat,
                     GLenum format,
                     GLenum type,
                     const void *data);

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
     * @param type              Data type of the pixel data. Must be one of GL_UNSIGNED_BYTE, GL_BYTE,
     * GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT and etc.
     *
     * @param                   Data Pointer to the image data in memory
     */
    explicit Texture(Core &core,
                     unsigned int width,
                     unsigned int height,
                     GLint internalFormat,
                     GLenum format,
                     GLenum type,
                     const void *data);

    /**
     * @brief                   Initialize as 2D texture
     *
     * https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage3D.xhtml
     *
     * @param core              Game core object
     * @param width             Texture width in pixels
     * @param height            Texture height in pixels
     * @param depth             Texture depth in pixels
     * @param internalFormat    Number of color components in the texture
     *
     * @param format            Format of the pixel data. Must be one of GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA,
     * GL_BGRA, GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER,
     * GL_STENCIL_INDEX, GL_DEPTH_COMPONENT or GL_DEPTH_STENCIL
     *
     * @param type              Data type of the pixel data. Must be one of GL_UNSIGNED_BYTE, GL_BYTE,
     * GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT and etc.
     *
     * @param                   Data Pointer to the image data in memory
     */
    explicit Texture(Core &core,
                     unsigned int width,
                     unsigned int height,
                     unsigned int depth,
                     GLint internalFormat,
                     GLenum format,
                     GLenum type,
                     const void *data);

    ~Texture();

    /**
     * @brief                   Set this texture as current on specified slot
     * @param slot              Texture slot
     */
    void bind(size_t slot);

    /**
     * @brief           Change size of texture
     *
     * Only needed components will be used.
     * E.g. for TEXTURE_2D - width and height.
     *
     * @param width     New texture with in pixels
     * @param height    New texture height in pixels
     * @param depth     New texture depth in pixels
     */
    void resize(unsigned int width, unsigned int height = 0, unsigned int depth = 0);

    /**
     * @brief           Change sampling arithmetic
     *
     * When this function is called before initialization, it just set parameters locally. When it is called after
     * initialization it will change OpenGL state of this texture.
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
     * @return Native OpenGL handle
     */
    GLuint getHandle() const;

    /**
     * @return Target to which the texture is bound
     */
    GLenum getTarget() const;

    /**
     * @return Texture dimensions. Useless components will be zeroed
     */
    const glm::uvec3 &getSize() const;

private:
    static constexpr auto DEFAULT_TEXTURE_UNIT = 15u;

    std::shared_ptr<RenderingManager> m_renderingManager;

    GLuint m_id = 0;
    GLenum m_target = GL_TEXTURE_2D;

    GLint m_internalFormat = GL_RGBA;
    GLenum m_format = GL_RGBA;
    GLenum m_type = GL_UNSIGNED_BYTE;

    GLint m_minFilter = GL_LINEAR;
    GLint m_magFilter = GL_LINEAR;

    GLint m_wrapS = GL_REPEAT;
    GLint m_wrapT = GL_REPEAT;
    GLint m_wrapR = GL_REPEAT;

    glm::uvec3 m_size{};
};

}  // namespace core
