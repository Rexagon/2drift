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
    while (!m_scenes.empty())
    {
        m_scenes.top()->onLeave();
        m_scenes.top()->onClose();
        m_scenes.pop();
    }
}


void SceneManager::handleEvent(const sf::Event &e)
{
    m_scenes.top()->handleEvent(e);
}


void SceneManager::update(double dt)
{
    m_scenes.top()->onUpdate(dt);
}


void SceneManager::applyActions()
{
    // Execute all actions
    while (!m_actionsQueue.empty())
    {
        auto action = std::move(m_actionsQueue.front());

        switch (action.first)
        {
            case ActionType::PUSH:
                // Leave from current scene
                if (!m_scenes.empty())
                {
                    m_scenes.top()->onLeave();
                }

                // Init and enter next scene
                action.second->onInit();
                action.second->onEnter();
                m_scenes.emplace(std::move(action.second));
                break;

            case ActionType::POP:
                // Leave and close current scene
                if (!m_scenes.empty())
                {
                    m_scenes.top()->onLeave();
                    m_scenes.top()->onClose();
                    m_scenes.pop();
                }

                // Enter previous scene
                if (!m_scenes.empty())
                {
                    m_scenes.top()->onEnter();
                }
                break;
        }

        m_actionsQueue.pop();
    }

    // Close game if empty
    if (m_scenes.empty())
    {
        getCore().requestExit();
        return;
    }
}


void SceneManager::pop()
{
    m_actionsQueue.emplace(ActionType::POP, nullptr);
}


void SceneManager::onInit()
{
    applyActions();
}


Scene::Scene(Core &core)
    : m_core{core}
{
}


Core &Scene::getCore()
{
    return m_core;
}

}  // namespace core
