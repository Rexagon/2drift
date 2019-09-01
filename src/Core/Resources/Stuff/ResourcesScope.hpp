#pragma once

#include <unordered_set>

#include "Core/Managers/ResourceManager.hpp"

namespace core
{
/**
 * @brief   Resource scope
 *
 * Used for smart resource unloading
 */
class ResourcesScope final
{
public:
    /**
     * @brief       Create empty resource scope
     * @param core  Game core object
     */
    explicit ResourcesScope(Core &core);

    /**
     * @brief       Unbinds and clears all resources binded by this scope
     */
    ~ResourcesScope();

    /**
     * @brief           Bind resource loader with specified type and name
     * @tparam T        Type of resource
     * @param name      Name of resource
     * @param loader    Resource loader
     * @param load      Whether to load immediately. False by default
     */
    template <typename T>
    void bind(const std::string &name, const ResourceManager::Loader &loader, bool load = false);

    template <typename T>
    std::weak_ptr<T> get(const std::string &name);

    template <typename T>
    std::weak_ptr<T> get(const std::string &name, const ResourceManager::Loader &loader);

private:
    std::shared_ptr<ResourceManager> m_resourceManager;

    std::unordered_set<ResourceManager::Key, ResourceManager::KeyHash> m_resources{};
};


template <typename T>
void ResourcesScope::bind(const std::string &name, const core::ResourceManager::Loader &loader, bool load)
{
    const auto key = ResourceManager::createKey<T>(name);

    m_resources.emplace(key);
    m_resourceManager->bind(key, loader);

    if (load)
    {
        m_resourceManager->get(key);
    }
}


template <typename T>
std::weak_ptr<T> ResourcesScope::get(const std::string &name)
{
    return m_resourceManager->get<T>(name);
}


template <typename T>
std::weak_ptr<T> ResourcesScope::get(const std::string &name, const ResourceManager::Loader &loader)
{
    return m_resourceManager->get<T>(name, loader);
}

}  // namespace core
