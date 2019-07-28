// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ResourceManager.hpp"

namespace core
{
ResourceManager::ResourceManager(Core &core)
    : Manager{core}
{
}


std::weak_ptr<void> ResourceManager::get(const ResourceManager::Key &key)
{
    // Find loaded resource first
    const auto resourceIt = m_resources.find(key);
    if (resourceIt != m_resources.end())
    {
        return resourceIt->second;
    }

    // If resource was not loaded - find loader
    const auto loaderId = m_loaders.find(key);
    if (loaderId == m_loaders.end())
    {
        throw std::runtime_error{"Unable to find resource '" + key.first + "' of type " + key.second.name()};
    }

    auto [it, success] = m_resources.emplace(key, loaderId->second());
    assert(success);

    return it->second;
}


void ResourceManager::bind(const core::ResourceManager::Key &key, const core::ResourceManager::Loader &loader)
{
    m_loaders.emplace(key, loader);
}


void ResourceManager::unbind(const core::ResourceManager::Key &key)
{
    const auto it = m_loaders.find(key);

    if (it != m_loaders.end())
    {
        m_loaders.erase(it);
    }
}


void ResourceManager::clear(const core::ResourceManager::Key &key)
{
    const auto it = m_resources.find(key);

    if (it != m_resources.end())
    {
        m_resources.erase(it);
    }
}


bool ResourceManager::hasLoader(const core::ResourceManager::Key &key)
{
    return m_resources.find(key) != m_resources.end();
}


bool ResourceManager::isResourceLoaded(const core::ResourceManager::Key &key)
{
    const auto it = m_resources.find(key);
    return it != m_resources.end() && it->second != nullptr;
}

}  // namespace core
