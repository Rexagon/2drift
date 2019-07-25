#pragma once

#include <cassert>
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "Managers/Manager.hpp"

namespace core
{
class Core
{
public:
    void init();

    void requestExit();

    bool isPendingStop() const;

    template <typename T, typename... Args>
    void bind(Args &&... args);

    template <typename T>
    void unbind();

    template <typename T>
    std::weak_ptr<T> get();

    template <typename T>
    bool has() const;

private:
    bool m_isPendingStop;

    std::unordered_map<std::type_index, std::shared_ptr<Manager>> m_managers;
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
