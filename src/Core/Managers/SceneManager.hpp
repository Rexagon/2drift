#pragma once

#include <memory>
#include <queue>
#include <stack>

#include "Core/Managers/Stuff/Scene.hpp"
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
    void handleEvent(const Event &e);

    /**
     * @brief       Update current scene
     * @param dt    Time in seconds since last frame
     *
     * Function behaviour is undefined when it is called from scene.
     */
    void update(float dt);

    /**
     * @brief       Open specified scene in the end of current frame
     * @param scene Scene object
     */
    void openScene(std::unique_ptr<Scene> scene);

private:
    std::unique_ptr<Scene> m_currentScene;
    std::unique_ptr<Scene> m_nextScene;
};

}  // namespace core
