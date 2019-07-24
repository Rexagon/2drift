#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "Manager.hpp"

namespace app
{
class WindowManager : public Manager
{
public:
    explicit WindowManager(Core &core, const sf::Vector2u &size, const std::string &title);

    void setSize(const sf::Vector2u &size);

    void setTitle(const std::string &title);

    void setVsyncEnabled(bool enabled);

    sf::Vector2u getSize() const;

    bool isVsyncEnabled() const;

    sf::RenderWindow &getWindow();

private:
    void onInit() override;

    struct
    {
        sf::Vector2u size;
        std::string title;
    } m_options;

    bool m_isVsyncEnabled = true;

    std::unique_ptr<sf::RenderWindow> m_renderWindow;
};

}  // namespace app
