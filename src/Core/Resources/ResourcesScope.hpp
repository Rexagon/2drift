#pragma once

#include <unordered_set>

#include "Core/Managers/ResourceManager.hpp"

namespace core
{
class ResourcesScope final
{
public:
    explicit ResourcesScope(Core &core);

    ~ResourcesScope();

    template <typename T>
    void bind(const std::string &name, const ResourceManager::Loader &loader);



private:
    std::shared_ptr<ResourceManager> m_resourceManager;

    std::unordered_set<ResourceManager::Key, ResourceManager::KeyHash> m_resources;
};


template <typename T>
void ResourcesScope::bind(const std::string &name, const core::ResourceManager::Loader &loader)
{
    const auto key = ResourceManager::createKey<T>(name);

    m_resources.emplace(key);
    m_resourceManager->bind(key, loader);
}

}  // namespace core
