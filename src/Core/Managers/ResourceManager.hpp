#pragma once

#include <cassert>
#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "Core/Stuff/Hash.hpp"
#include "Manager.hpp"

namespace core
{
class ResourceManager final : public Manager
{
public:
    using Key = std::pair<std::string, std::type_index>;
    using Loader = std::function<std::shared_ptr<void>()>;

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


    std::weak_ptr<void> get(const Key &key);

    void bind(const Key &key, const Loader &loader);

    void unbind(const Key &key);

    void clear(const Key &key);

    bool hasLoader(const Key &key);

    bool isResourceLoaded(const Key &key);


    template <typename T>
    static inline Key createKey(const std::string &name);

private:
    std::unordered_map<Key, Loader, KeyHash> m_loaders;
    mutable std::unordered_map<Key, std::shared_ptr<void>, KeyHash> m_resources;
};


template <typename T>
std::weak_ptr<T> ResourceManager::get(const std::string &name)
{
    return std::static_pointer_cast<T>(get(createKey<T>(name)).lock());
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
inline ResourceManager::Key ResourceManager::createKey(const std::string &name)
{
    return std::pair{name, std::type_index{typeid(T)}};
}

}  // namespace core
