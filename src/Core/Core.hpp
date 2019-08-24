#pragma once

#include <cassert>
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "Managers/Manager.hpp"

namespace core
{
/**
 * @brief   Game state container
 */
class Core
{
public:
    /**
     * @brief   Initialize all managers
     */
    void init();

    void requestExit();

    /**
     * @return true of exit was requested
     */
    bool isPendingStop() const;

    /**
     * @brief       Create and bind manager
     * @tparam T    Type of manager
     * @tparam Args Manager constructor argument types
     * @param args  Manager constructor arguments
     */
    template <typename T, typename... Args>
    void bind(Args &&... args);

    /**
     * @brief       Remove manager
     * @tparam T    Type of manager
     */
    template <typename T>
    void unbind();

    /**
     * @brief       Get manager of type
     * @tparam T    Type of manager
     * @return      Manager
     */
    template <typename T>
    std::weak_ptr<T> get();

    /**
     * @brief       Check if manager of specified type was binded
     * @tparam T    Type of manager
     * @return      true if manager exists
     */
    template <typename T>
    bool has() const;

private:
    bool m_isPendingStop{false};

    std::unordered_map<std::type_index, std::shared_ptr<Manager>> m_managers{};
};


template <typename T, typename... Args>
void Core::bind(Args &&... args)
{
    static_assert(std::is_base_of_v<Manager, T>, "T must be a child class of Manager");
    assert(!has<T>());

    m_managers.emplace(std::type_index{typeid(T)}, std::make_shared<T>(*this, std::forward<Args>(args)...));
}


template <typename T>
void Core::unbind()
{
    static_assert(std::is_base_of_v<Manager, T>, "T must be a child class of Manager");

    const auto it = m_managers.find(std::type_index{typeid(T)});
    if (it != m_managers.end())
    {
        m_managers.erase(it);
    }
}


template <typename T>
std::weak_ptr<T> Core::get()
{
    static_assert(std::is_base_of_v<Manager, T>, "T must be a child class of Manager");
    assert(has<T>());

    return std::dynamic_pointer_cast<T>(m_managers.find(std::type_index{typeid(T)})->second);
}


template <typename T>
bool Core::has() const
{
    static_assert(std::is_base_of_v<Manager, T>, "T must be a child class of Manager");

    const auto it = m_managers.find(std::type_index{typeid(T)});
    return it != m_managers.end() && it->second != nullptr;
}

}  // namespace core
