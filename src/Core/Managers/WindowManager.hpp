#pragma once

#include <memory>
#include <queue>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/vec2.hpp>

#include "Core/Stuff/Event.hpp"
#include "Manager.hpp"

namespace core
{
/**
 * @brief   Window manager
 *
 * Store window object
 */
class WindowManager final : public Manager
{
public:
    /**
     * @brief           Create window with specified size and title
     * @param core      Game core object
     * @param size      Window size in pixels
     * @param title     Window title
     */
    explicit WindowManager(Core &core, const glm::uvec2 &size, const std::string &title);
    ~WindowManager() override;

    void display();

    bool pollEvent(Event &event);

    void setSize(const glm::uvec2 &size);
    const glm::uvec2 &getSize() const;

    void setTitle(const std::string &title);
    const std::string &getTitle() const;

    void setVsyncEnabled(bool enabled);

    bool isVsyncEnabled() const;

    const GLFWwindow *getWindow() const;

private:
    void onInit() override;

    void registerCallbacks();

    glm::uvec2 m_size;
    std::string m_title;
    bool m_isVsyncEnabled{true};

    GLFWwindow *m_window{nullptr};

    std::queue<Event> m_events{};
};

}  // namespace core
