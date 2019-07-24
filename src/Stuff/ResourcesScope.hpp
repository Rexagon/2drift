#pragma once

#include <unordered_set>

#include "Managers/ResourceManager.hpp"

namespace app
{
class ResourcesScope final
{
public:
    explicit ResourcesScope(const std::shared_ptr<ResourceManager> &manager);

    ~ResourcesScope();

    template <typename T>
    void bind(const std::string &name, const ResourceManager::Loader &loader);

private:
    std::shared_ptr<ResourceManager> m_resourceManager;

    std::unordered_set<ResourceManager::Key, ResourceManager::KeyHash> m_resources;
};


template <typename T>
void ResourcesScope::bind(const std::string &name, const app::ResourceManager::Loader &loader)
{
    const auto key = ResourceManager::createKey<T>(name);

    m_resources.emplace(key);
    m_resourceManager->bind(key, loader);
}

}  // namespace app
