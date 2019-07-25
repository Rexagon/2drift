// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "WindowManager.hpp"

#include "Core/Core.hpp"

namespace core
{
WindowManager::WindowManager(core::Core &core, const sf::Vector2u &size, const std::string &title)
    : Manager{core}
    , m_options{size, title}
{
}


void WindowManager::onInit()
{
    m_renderWindow =
        std::make_unique<sf::RenderWindow>(sf::VideoMode{m_options.size.x, m_options.size.y}, m_options.title);

    setVsyncEnabled(m_isVsyncEnabled);
}


void WindowManager::setSize(const sf::Vector2u &size)
{
    assert(m_renderWindow != nullptr);

    m_renderWindow->setSize(size);
}


void WindowManager::setTitle(const std::string &title)
{
    assert(m_renderWindow != nullptr);

    m_renderWindow->setTitle(title);
}


void WindowManager::setVsyncEnabled(bool enabled)
{
    assert(m_renderWindow != nullptr);

    m_isVsyncEnabled = enabled;
    m_renderWindow->setVerticalSyncEnabled(enabled);
}


sf::Vector2u WindowManager::getSize() const
{
    assert(m_renderWindow != nullptr);

    return m_renderWindow->getSize();
}


bool WindowManager::isVsyncEnabled() const
{
    return m_isVsyncEnabled;
}


sf::RenderWindow &WindowManager::getWindow()
{
    assert(m_renderWindow != nullptr);

    return *m_renderWindow;
}

}  // namespace core
