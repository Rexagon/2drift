// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "TextureLoader.hpp"

#include <stb/stb_image.h>

#include "Core/Core.hpp"
#include "Core/Rendering/Texture.hpp"

namespace core
{
TextureLoader::TextureLoader(Core &core, const std::string &path)
    : m_core{core}
    , m_fileManager{core.get<FileManager>().lock()}
    , m_path{path}
{
}


std::shared_ptr<void> TextureLoader::operator()()
{
    const auto data = m_fileManager->load(m_path);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    auto *image = stbi_load_from_memory(reinterpret_cast<const uint8_t *>(data.data()), static_cast<int>(data.size()),
                                        &width, &height, &channels, STBI_rgb_alpha);

    if (image == nullptr)
    {
        throw std::runtime_error{"Unable to load texture: " + m_path};
    }

    if (channels < 3)
    {
        stbi_image_free(static_cast<void *>(image));
        throw std::runtime_error{"Unsupported texture format: " + m_path};
    }

    GLint internalFormat = channels == 3 ? GL_RGB8 : GL_RGBA8;
    GLenum format = channels == 3 ? GL_RGB : GL_RGBA;

    auto texture =
        std::make_shared<Texture>(m_core, glm::uvec2{width, height}, internalFormat, format, GL_UNSIGNED_BYTE, image);
    stbi_image_free(static_cast<void *>(image));

    return texture;
}

}  // namespace core
