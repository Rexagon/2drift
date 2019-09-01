#pragma once

#include "Core/Core.hpp"
#include "Core/Stuff/Event.hpp"

namespace core
{
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
    virtual void handleEvent(const Event &e);

    /**
     * @brief       Called every frame
     * @param dt    Time in seconds since last frame
     */
    virtual void update(float dt);

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
