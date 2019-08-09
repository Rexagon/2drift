// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "SceneManager.hpp"

#include "Core/Core.hpp"

namespace core
{
SceneManager::SceneManager(Core &core)
    : Manager{core}
{
}


SceneManager::~SceneManager()
{
    if (m_currentScene != nullptr)
    {
        m_currentScene->close();
    }

    m_nextScene.reset();
    m_currentScene.reset();
}


void SceneManager::handleEvent(const sf::Event &e)
{
    m_currentScene->handleEvent(e);
}


void SceneManager::update(double dt)
{
    m_currentScene->update(dt);

    if (m_nextScene != nullptr)
    {
        m_currentScene->close();
        m_currentScene = std::move(m_nextScene);

        m_currentScene->init();
    }
}


void SceneManager::openScene(std::unique_ptr<Scene> scene)
{
    assert(scene != nullptr);

    if (m_currentScene == nullptr)
    {
        m_currentScene = std::move(scene);
    }
    else
    {
        m_nextScene = std::move(scene);
    }
}

}  // namespace core
