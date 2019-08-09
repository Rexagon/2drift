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
     * @brief       Open specified scene in the end of current frame
     * @param scene Scene object
     */
    void openScene(std::unique_ptr<Scene> scene);

private:
    std::unique_ptr<Scene> m_currentScene;
    std::unique_ptr<Scene> m_nextScene;
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
     * @brief       Called when scene becomes current
     */
    virtual void init();

    /**
     * @brief       Called when scene stops being current
     */
    virtual void close();

    /**
     * @brief       Called on every window event before Scene::update
     * @param e     Event from window
     */
    virtual void handleEvent(const sf::Event &e);

    /**
     * @brief       Called every frame
     * @param dt    Time in seconds since last frame
     */
    virtual void update(double dt);

protected:
    inline Core &getCore();

private:
    Core &m_core;
};


inline Core &Scene::getCore()
{
    return m_core;
}

}  // namespace core
