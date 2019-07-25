#pragma once

#include <memory>
#include <queue>
#include <stack>

#include <SFML/Window/Event.hpp>

#include "Manager.hpp"

namespace core
{
class Scene;

class SceneManager final : public Manager
{
    enum class ActionType
    {
        PUSH,
        POP
    };

    using Action = std::pair<ActionType, std::unique_ptr<Scene>>;

public:
    explicit SceneManager(Core &core);

    ~SceneManager() override;

    void handleEvent(const sf::Event &e);

    void update(double dt);

    void applyActions();

    template <typename T, typename... Args>
    void push(Args &&... args);

    void pop();

private:
    void onInit() override;

    std::queue<Action> m_actionsQueue;

    std::stack<std::unique_ptr<Scene>> m_scenes;
};


class Scene
{
public:
    explicit Scene(Core &core);

    virtual ~Scene() = default;

    virtual void onInit()
    {
    }

    virtual void onClose()
    {
    }

    virtual void onEnter()
    {
    }

    virtual void onLeave()
    {
    }

    virtual void onUpdate(double dt)
    {
    }

    virtual void handleEvent(const sf::Event &e)
    {
    }

protected:
    Core &getCore();

private:
    Core &m_core;
};


template <typename T, typename... Args>
void SceneManager::push(Args &&... args)
{
    static_assert(std::is_base_of_v<Scene, T>, "T must be a child class of Scene");

    m_actionsQueue.emplace(ActionType::PUSH, std::make_unique<T>(getCore(), std::forward<Args>(args)...));
}


}  // namespace core
