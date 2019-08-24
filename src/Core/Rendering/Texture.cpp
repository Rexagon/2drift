// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Core/Rendering/Texture.hpp"

#include "Core/Core.hpp"

namespace core
{
Texture::Texture(Core &core,
                 const unsigned int width,
                 const GLint internalFormat,
                 const GLenum format,
                 const GLenum type,
                 const void *data)
    : m_renderingManager{core.get<RenderingManager>().lock()}
    , m_target{GL_TEXTURE_1D}
{
    glGenTextures(1, &m_id);

    m_size = glm::ivec3(width, 0, 0);
    m_internalFormat = internalFormat;
    m_format = format;
    m_type = type;

    m_renderingManager->bindTexture(m_target, m_id, DEFAULT_TEXTURE_UNIT);

    glTexImage1D(m_target, 0, internalFormat, static_cast<GLsizei>(width), 0, format, type, data);

    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, m_minFilter);
    glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, m_magFilter);
    glTexParameteri(m_target, GL_TEXTURE_WRAP_S, m_wrapS);
}


Texture::Texture(Core &core,
                 const unsigned int width,
                 const unsigned int height,
                 const GLint internalFormat,
                 const GLenum format,
                 const GLenum type,
                 const void *data)
    : m_renderingManager{core.get<RenderingManager>().lock()}
    , m_target{GL_TEXTURE_2D}
{
    glGenTextures(1, &m_id);

    m_size = glm::uvec3(width, height, 0);
    m_internalFormat = internalFormat;
    m_format = format;
    m_type = type;

    m_renderingManager->bindTexture(m_target, m_id, DEFAULT_TEXTURE_UNIT);

    glTexImage2D(m_target, 0, internalFormat, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, format,
                 type, data);

    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, m_minFilter);
    glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, m_magFilter);
    glTexParameteri(m_target, GL_TEXTURE_WRAP_S, m_wrapS);
    glTexParameteri(m_target, GL_TEXTURE_WRAP_T, m_wrapT);
}


Texture::Texture(Core &core,
                 const unsigned int width,
                 const unsigned int height,
                 const unsigned int depth,
                 const GLint internalFormat,
                 const GLenum format,
                 const GLenum type,
                 const void *data)
    : m_renderingManager{core.get<RenderingManager>().lock()}
    , m_target{GL_TEXTURE_3D}
{
    glGenTextures(1, &m_id);

    m_size = glm::uvec3(width, height, depth);
    m_internalFormat = internalFormat;
    m_format = format;
    m_type = type;

    m_renderingManager->bindTexture(m_target, m_id, DEFAULT_TEXTURE_UNIT);

    glTexImage3D(m_target, 0, internalFormat, static_cast<GLsizei>(width), static_cast<GLsizei>(height),
                 static_cast<GLsizei>(depth), 0, format, type, data);

    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, m_minFilter);
    glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, m_magFilter);
    glTexParameteri(m_target, GL_TEXTURE_WRAP_S, m_wrapS);
    glTexParameteri(m_target, GL_TEXTURE_WRAP_T, m_wrapT);
    glTexParameteri(m_target, GL_TEXTURE_WRAP_R, m_wrapR);
}


Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}


void Texture::bind(size_t slot)
{
    m_renderingManager->bindTexture(m_target, m_id, slot);
}


void Texture::resize(const unsigned int width, const unsigned int height, const unsigned int depth)
{
    m_renderingManager->bindTexture(m_target, m_id, DEFAULT_TEXTURE_UNIT);

    switch (m_target)
    {
        case GL_TEXTURE_1D:
            if (width == 0)
                return;
            m_size.x = width;
            glTexImage1D(GL_TEXTURE_1D, 0, m_internalFormat, static_cast<int>(width), 0, m_format, m_type, nullptr);
            break;

        case GL_TEXTURE_2D:
            if (width == 0 || height == 0)
                return;
            m_size.x = width;
            m_size.y = height;
            glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, static_cast<int>(width), static_cast<int>(height), 0,
                         m_format, m_type, nullptr);
            break;

        case GL_TEXTURE_3D:
            if (width == 0 || height == 0 || depth == 0)
                return;
            m_size.x = width;
            m_size.y = height;
            m_size.z = height;
            glTexImage3D(GL_TEXTURE_3D, 0, m_internalFormat, static_cast<int>(width), static_cast<int>(height),
                         static_cast<int>(depth), 0, m_format, m_type, nullptr);
            break;

        default:
            break;
    }
}


void Texture::setFilters(const GLint minFilter, const GLint magFilter)
{
    if (m_minFilter == minFilter && m_magFilter == magFilter)
    {
        return;
    }

    m_renderingManager->bindTexture(m_target, m_id, DEFAULT_TEXTURE_UNIT);

    if (m_minFilter != minFilter)
    {
        m_minFilter = minFilter;
        glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, minFilter);
    }

    if (m_magFilter != magFilter)
    {
        m_magFilter = magFilter;
        glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, magFilter);
    }
}


void Texture::setWrapMode(const GLint wrapMode)
{
    switch (m_target)
    {
        case GL_TEXTURE_3D:
            setWrapMode(wrapMode, 2);
            [[fallthrough]];

        case GL_TEXTURE_2D:
            setWrapMode(wrapMode, 1);
            [[fallthrough]];

        case GL_TEXTURE_1D:
            setWrapMode(wrapMode, 0);
            [[fallthrough]];

        default:
            break;
    }
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

        case 2:
            wrapVariable = &m_wrapR;
            wrapComponent = GL_TEXTURE_WRAP_R;
            break;

        default:
            return;
    }

    if (*wrapVariable != wrapMode)
    {
        *wrapVariable = wrapMode;

        m_renderingManager->bindTexture(m_target, m_id, DEFAULT_TEXTURE_UNIT);
        glTexParameteri(m_target, wrapComponent, wrapMode);
    }
}


void Texture::generateMipmap() const
{
    m_renderingManager->bindTexture(m_target, m_id, DEFAULT_TEXTURE_UNIT);
    glGenerateMipmap(m_target);
}


GLuint Texture::getHandle() const
{
    return m_id;
}


GLenum Texture::getTarget() const
{
    return m_target;
}


const glm::uvec3 &Texture::getSize() const
{
    return m_size;
}


}  // namespace core
