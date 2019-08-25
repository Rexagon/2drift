// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Core/Rendering/Texture.hpp"

#include "Core/Core.hpp"

namespace
{
constexpr auto DEFAULT_TEXTURE_UNIT = 15u;
}


namespace core
{
Texture::Texture(Core &core,
                 const glm::uvec2 &size,
                 const GLint internalFormat,
                 const GLenum format,
                 const GLenum pixelType,
                 const void *data)
    : m_renderingManager{core.get<RenderingManager>().lock()}
    , m_size{size}
    , m_internalFormat{internalFormat}
    , m_format{format}
    , m_pixelType{pixelType}
{
    glGenTextures(1, &m_id);

    m_renderingManager->bindTexture(GL_TEXTURE_2D, m_id, DEFAULT_TEXTURE_UNIT);

    glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, static_cast<GLsizei>(m_size.x), static_cast<GLsizei>(m_size.y), 0,
                 m_format, m_pixelType, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapT);
}


Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}


void Texture::bind(size_t slot) const
{
    m_renderingManager->bindTexture(GL_TEXTURE_2D, m_id, slot);
}


void Texture::resize(const glm::uvec2 &size)
{
    if (size == m_size)
    {
        return;
    }

    m_renderingManager->bindTexture(GL_TEXTURE_2D, m_id, DEFAULT_TEXTURE_UNIT);

    glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, static_cast<GLsizei>(m_size.x), static_cast<GLsizei>(m_size.y), 0,
                 m_format, m_pixelType, nullptr);
}


void Texture::setFilters(const GLint minFilter, const GLint magFilter)
{
    if (m_minFilter == minFilter && m_magFilter == magFilter)
    {
        return;
    }

    m_renderingManager->bindTexture(GL_TEXTURE_2D, m_id, DEFAULT_TEXTURE_UNIT);

    if (m_minFilter != minFilter)
    {
        m_minFilter = minFilter;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    }

    if (m_magFilter != magFilter)
    {
        m_magFilter = magFilter;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    }
}


void Texture::setWrapMode(const GLint wrapMode)
{
    setWrapMode(wrapMode, 0);
    setWrapMode(wrapMode, 1);
}


void Texture::setWrapMode(const GLint wrapMode, const size_t component)
{
    GLenum wrapComponent = 0;
    GLint *wrapVariable = nullptr;
    switch (component)
    {
        case 0:
            wrapVariable = &m_wrapS;
            wrapComponent = GL_TEXTURE_WRAP_S;
            break;

        case 1:
            wrapVariable = &m_wrapT;
            wrapComponent = GL_TEXTURE_WRAP_T;
            break;

        default:
            return;
    }

    if (*wrapVariable != wrapMode)
    {
        *wrapVariable = wrapMode;

        m_renderingManager->bindTexture(GL_TEXTURE_2D, m_id, DEFAULT_TEXTURE_UNIT);
        glTexParameteri(GL_TEXTURE_2D, wrapComponent, wrapMode);
    }
}


void Texture::generateMipmap() const
{
    m_renderingManager->bindTexture(GL_TEXTURE_2D, m_id, DEFAULT_TEXTURE_UNIT);
    glGenerateMipmap(GL_TEXTURE_2D);
}


const glm::uvec2 &Texture::getSize() const
{
    return m_size;
}


GLuint Texture::getHandle() const
{
    return m_id;
}


}  // namespace core
