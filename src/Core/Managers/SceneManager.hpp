#pragma once

#include <memory>
#include <queue>
#include <stack>

#include <SFML/Window/Event.hpp>

#include "Manager.hpp"

namespace core
{
class Scene;

/**
 * @brief   Scene manager
 *
 * Handles scenes stack
 */
class SceneManager final : public Manager
{
    enum class ActionType
    {
        PUSH,
        POP
    };

    using Action = std::pair<ActionType, std::unique_ptr<Scene>>;

public:
    /**
     * @brief       Create manager with empty scenes stack
     * @param core
     */
    explicit SceneManager(Core &core);

    /**
     * @brief       Pops all scene sequentially
     */
    ~SceneManager() override;

    /**
     * @brief       Propagate event to current scene
     * @param e     Event from window
     *
     * Function behaviour is undefined when it is called from scene.
     */
    void handleEvent(const sf::Event &e);

    /**
     * @brief       Update current scene
     * @param dt    Time in seconds since last frame
     *
     * Function behaviour is undefined when it is called from scene.
     */
    void update(double dt);

    /**
     * @brief       Apply all requested pushes and pops
     *
     * Function behaviour is undefined when it is called from scene.
     * Should be called after update
     */
    void applyActions();

    /**
     * @brief       Add 'push scene' action to the action queue
     *
     * Does not affect stack. Call SceneManager::applyActions
     *
     * @tparam T    Type of scene object
     * @tparam Args Scene object constructor argument types
     * @param args  Scene object constructor arguments
     */
    template <typename T, typename... Args>
    void push(Args &&... args);

    /**
     * @brief       Add 'pop scene' action to the action queue
     *
     * Does not affect stack. Call SceneManager::applyActions
     */
    void pop();

private:
    void onInit() override;

    std::queue<Action> m_actionsQueue;

    std::stack<std::unique_ptr<Scene>> m_scenes;
};


/**
 * @brief   Scene base class
 */
class Scene
{
public:
    explicit Scene(Core &core);

    virtual ~Scene() = default;

    /**
     * @brief       Called right before scene is added to stack
     */
    virtual void onInit()
    {
    }

    /**
     * @brief       Called right before scene is removed from stack
     */
    virtual void onClose()
    {
    }

    /**
     * @brief       Called when scene becomes current
     */
    virtual void onEnter()
    {
    }

    /**
     * @brief       Called when scene stops being current
     */
    virtual void onLeave()
    {
    }

    /**
     * @brief       Called every frame
     * @param dt    Time in seconds since last frame
     */
    virtual void onUpdate(double dt)
    {
    }

    /**
     * @brief       Called on every window event before Scene::onUpdate
     * @param e     Event from window
     */
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
