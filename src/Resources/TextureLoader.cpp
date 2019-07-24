// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "TextureLoader.hpp"

#include <SFML/Graphics/Texture.hpp>

#include "Core/Core.hpp"

namespace app
{
TextureLoader::TextureLoader(Core &core, const std::string &path)
    : TextureLoader{core.get<FileManager>().lock(), path}
{
}


TextureLoader::TextureLoader(const std::shared_ptr<FileManager> &fileManager, const std::string &path)
    : m_fileManager{fileManager}
    , m_path{path}
{
}


std::shared_ptr<void> TextureLoader::operator()()
{
    const auto data = m_fileManager->load(m_path);

    auto texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromMemory(data.data(), data.size()))
    {
        throw std::runtime_error{"Unable to load texture: " + m_path};
    }

    return texture;
}

}  // namespace app
