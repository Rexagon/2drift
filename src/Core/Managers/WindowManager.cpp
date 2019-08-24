// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "WindowManager.hpp"

#include <iostream>

#include "Core/Core.hpp"

namespace core
{
WindowManager::WindowManager(core::Core &core, const glm::uvec2 &size, const std::string &title)
    : Manager{core}
    , m_size{size}
    , m_title{title}
{
    glfwSetErrorCallback([](int error, const char *description) {
        std::cerr << "GLFW ERROR: " << error << " " << description << std::endl;
    });
}


WindowManager::~WindowManager()
{
    glfwTerminate();
}


void WindowManager::display()
{
    assert(m_window != nullptr);
    assert(m_events.empty());

    glfwSwapBuffers(m_window);
    glfwPollEvents();
}


bool WindowManager::pollEvent(Event &event)
{
    if (m_events.empty())
    {
        return false;
    }

    event = m_events.front();
    m_events.pop();
    return true;
}


void WindowManager::setSize(const glm::uvec2 &size)
{
    assert(m_window != nullptr);

    m_size = size;
    glfwSetWindowSize(m_window, static_cast<int>(m_size.x), static_cast<int>(m_size.y));
}


const glm::uvec2 &WindowManager::getSize() const
{
    return m_size;
}


void WindowManager::setTitle(const std::string &title)
{
    assert(m_window != nullptr);

    m_title = title;
    glfwSetWindowTitle(m_window, m_title.c_str());
}


const std::string &WindowManager::getTitle() const
{
    return m_title;
}


void WindowManager::setVsyncEnabled(bool enabled)
{
    m_isVsyncEnabled = enabled;
    glfwSwapInterval(static_cast<int>(enabled));
}


bool WindowManager::isVsyncEnabled() const
{
    return m_isVsyncEnabled;
}


const GLFWwindow *WindowManager::getWindow() const
{
    return m_window;
}


void WindowManager::onInit()
{
    // Initialize GLFW
    if (glfwInit() != GLFW_TRUE)
    {
        throw std::runtime_error{"Unable to initialize glfw"};
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    m_window = glfwCreateWindow(static_cast<int>(m_size.x), static_cast<int>(m_size.y), m_title.c_str(),
                                nullptr /* GLFW monitor */, nullptr /* Shared window */);

    if (m_window == nullptr)
    {
        throw std::runtime_error{"Unable to create window"};
    }

    glfwMakeContextCurrent(m_window);

    // Initialize glad
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        throw std::runtime_error{"Unable to initialize glad"};
    }

    // Register callbacks
    registerCallbacks();
}


void WindowManager::registerCallbacks()
{
    glfwSetWindowUserPointer(m_window, this);

    // Event::Type::Closed
    glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window) {
        auto self = reinterpret_cast<WindowManager *>(glfwGetWindowUserPointer(window));

        Event event;
        event.type = Event::Type::Closed;
        self->m_events.emplace(event);
    });

    // Event::Type::Resized
    glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height) {
        auto self = reinterpret_cast<WindowManager *>(glfwGetWindowUserPointer(window));

        self->m_size = glm::uvec2{width, height};

        Event event;
        event.type = Event::Type::Resized;
        event.size = Event::SizeEvent{glm::uvec2{width, height}};
        self->m_events.emplace(event);
    });

    // Event::Type::KeyPressed, Event::Type::KeyReleased
    glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_UNKNOWN || action == GLFW_REPEAT)
        {
            return;
        }

        auto self = reinterpret_cast<WindowManager *>(glfwGetWindowUserPointer(window));

        Event event;
        event.type = action == GLFW_PRESS ? Event::Type::KeyPressed : Event::Type::KeyReleased;
        event.key = Event::KeyEvent{scancode, static_cast<uint16_t>(key), static_cast<uint8_t>(mods)};
        self->m_events.emplace(event);
    });

    // Event::Type::TextEntered
    glfwSetCharCallback(m_window, [](GLFWwindow *window, unsigned int code) {
        auto self = reinterpret_cast<WindowManager *>(glfwGetWindowUserPointer(window));

        Event event;
        event.type = Event::Type::TextEntered;
        event.text = Event::TextEvent{code};
        self->m_events.emplace(event);
    });

    // Event::Type::MouseMoved
    glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double x, double y) {
        auto self = reinterpret_cast<WindowManager *>(glfwGetWindowUserPointer(window));

        Event event;
        event.type = Event::Type::MouseMoved;
        event.mouseMove = Event::MouseMoveEvent{glm::vec2{x, y}};
        self->m_events.emplace(event);
    });

    // Event::Type::MouseButtonPressed, Event::Type::MouseButtonReleased
    glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods) {
        auto self = reinterpret_cast<WindowManager *>(glfwGetWindowUserPointer(window));

        Event event;
        event.type = action == GLFW_PRESS ? Event::Type::MouseButtonPressed : Event::Type::MouseButtonReleased;
        event.mouseButton = Event::MouseButtonEvent{static_cast<uint8_t>(button), static_cast<uint8_t>(mods)};
        self->m_events.emplace(event);
    });

    // Event::Type::Scrolled
    glfwSetScrollCallback(m_window, [](GLFWwindow *window, double x, double y) {
        auto self = reinterpret_cast<WindowManager *>(glfwGetWindowUserPointer(window));

        Event event;
        event.type = Event::Type::Scrolled;
        event.scroll = Event::ScrollEvent{glm::vec2{x, y}};
        self->m_events.emplace(event);
    });
}

}  // namespace core
