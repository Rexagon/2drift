#pragma once

#include <cassert>
#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "Manager.hpp"
#include "Stuff/Hash.hpp"

namespace app
{
class ResourceManager : public Manager
{
    using Key = std::pair<std::string, std::type_index>;

    struct KeyHash
    {
        std::size_t operator()(const Key &key) const
        {
            size_t seed{};
            hash::combine(seed, key.first);
            hash::combine(seed, key.second);
            return seed;
        }
    };

public:
    using Loader = std::function<std::shared_ptr<void>()>;

    explicit ResourceManager(Core &core);


    template <typename T>
    std::weak_ptr<T> get(const std::string &name);


    template <typename T>
    inline void bind(const std::string &name, const Loader &loader);

    template <typename T>
    inline void unbind(const std::string &name);

    template <typename T>
    void clear(const std::string &name);

    template <typename T>
    inline bool hasLoader(const std::string &name) const;

    template <typename T>
    inline bool isResourceLoaded(const std::string &name) const;


    void bind(const Key &key, const Loader &loader);

    void unbind(const Key &key);

    void clear(const Key &key);

    bool hasLoader(const Key &key);

    bool isResourceLoaded(const Key &key);


    template <typename T>
    inline Key createKey(const std::string &name) const;

private:
    std::unordered_map<Key, Loader, KeyHash> m_loaders;
    mutable std::unordered_map<Key, std::shared_ptr<void>, KeyHash> m_resources;
};


template <typename T>
std::weak_ptr<T> ResourceManager::get(const std::string &name)
{
    const auto key = createKey<T>(name);

    // Find loaded resource first
    const auto resourceIt = m_resources.find(key);
    if (resourceIt != m_resources.end())
    {
        return std::static_pointer_cast<T>(resourceIt->second);
    }

    // If resource was not loaded - find loader
    const auto loaderId = m_loaders.find(key);
    if (loaderId == m_loaders.end())
    {
        throw std::runtime_error{"Unable to found for resource '" + name + "' of type " + key.second.name()};
    }

    auto [it, success] = m_resources.emplace(key, loaderId->second());
    assert(success);

    return std::static_pointer_cast<T>(it->second);
}


template <typename T>
inline void ResourceManager::bind(const std::string &name, const Loader &loader)
{
    bind(createKey<T>(name), loader);
}


template <typename T>
inline void ResourceManager::unbind(const std::string &name)
{
    unbind(createKey<T>(name));
}


template <typename T>
inline void ResourceManager::clear(const std::string &name)
{
    clear(createKey<T>(name));
}


template <typename T>
inline bool ResourceManager::hasLoader(const std::string &name) const
{
    return hasLoader(createKey<T>(name));
}


template <typename T>
inline bool ResourceManager::isResourceLoaded(const std::string &name) const
{
    return isResourceLoaded(createKey<T>(name));
}


template <typename T>
inline ResourceManager::Key ResourceManager::createKey(const std::string &name) const
{
    return std::pair{name, std::type_index{typeid(T)}};
}

}  // namespace app
