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
/**
 * @brief   Resource manager
 *
 * General store for named resources
 */
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

    /**
     * @brief           Create resource manager with empty store
     * @param core      Game core object
     */
    explicit ResourceManager(Core &core);

    /**
     * @brief           Get resource with specified type and name
     *
     * First access by {type,name} pair will try to load resource
     * by loader specified earlier by calling ResourceManager::bind function
     *
     * @tparam T        Type of resource
     * @param name      Name of resource
     * @return          Resource
     *
     * @throws          std::runtime_error if resource cannot be loaded
     */
    template <typename T>
    std::weak_ptr<T> get(const std::string &name);

    /**
     * @brief           Bind resource loader for specified type and name
     *
     * Further access by {type,name} pair will overwrite stored loader
     *
     * @tparam T        Type of resource
     * @param name      Name of resource
     * @param loader    Loader of resource
     */
    template <typename T>
    inline void bind(const std::string &name, const Loader &loader);

    /**
     * @brief           Unbind resource loader for specified type and name
     *
     * Only loader will be deleted from manager. If resources was not loaded
     * earlier, ResourceManager::bind must be called before accessing it
     *
     * @tparam T        Type of resource
     * @param name      Name of resource
     */
    template <typename T>
    inline void unbind(const std::string &name);

    /**
     * @brief           Unload resource stored in manager
     *
     * Removed resource reference from this manager if it was loaded before.
     * Do nothing otherwise.
     * Resource destructor will be called only if there is no other references
     * to it.
     *
     * @tparam T        Type of resource
     * @param name      Name of resource
     */
    template <typename T>
    void clear(const std::string &name);

    /**
     * @brief           Check if any resource loader was binded for specified type and name
     * @tparam T        Type of resource
     * @param name      Name of resource
     * @return          true if there is loader binded for specified type and name
     */
    template <typename T>
    inline bool hasLoader(const std::string &name) const;

    /**
     * @brief           Check if resource is loaded
     * @tparam T        Type of resource
     * @param name      Name of resource
     * @return          true if resource is loaded
     */
    template <typename T>
    inline bool isResourceLoaded(const std::string &name) const;


    std::weak_ptr<void> get(const Key &key);

    void bind(const Key &key, const Loader &loader);

    void unbind(const Key &key);

    void clear(const Key &key);

    bool hasLoader(const Key &key);

    bool isResourceLoaded(const Key &key);


    /**
     * @brief           Create key from specified type and name
     * @tparam T        Type of resource
     * @param name      Name of resource
     * @return          Resource key
     */
    template <typename T>
    static inline Key createKey(const std::string &name);

private:
    std::unordered_map<Key, Loader, KeyHash> m_loaders{};
    mutable std::unordered_map<Key, std::shared_ptr<void>, KeyHash> m_resources{};
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
