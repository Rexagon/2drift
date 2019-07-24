// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ResourceManager.hpp"

namespace app
{
ResourceManager::ResourceManager(Core &core)
    : Manager{core}
{
}


void ResourceManager::bind(const app::ResourceManager::Key &key, const app::ResourceManager::Loader &loader)
{
    m_loaders.emplace(key, loader);
}


void ResourceManager::unbind(const app::ResourceManager::Key &key)
{
    const auto it = m_loaders.find(key);

    if (it != m_loaders.end())
    {
        m_loaders.erase(it);
    }
}


void ResourceManager::clear(const app::ResourceManager::Key &key)
{
    const auto it = m_resources.find(key);

    if (it != m_resources.end())
    {
        m_resources.erase(it);
    }
}


bool ResourceManager::hasLoader(const app::ResourceManager::Key &key)
{
    return m_resources.find(key) != m_resources.end();
}


bool ResourceManager::isResourceLoaded(const app::ResourceManager::Key &key)
{
    const auto it = m_resources.find(key);
    return it != m_resources.end() && it->second != nullptr;
}

}  // namespace app
