#pragma once

#include <glm/vec2.hpp>

#include "Core/Stuff/Keyboard.hpp"
#include "Core/Stuff/Mouse.hpp"

namespace core
{
struct Event
{
    struct SizeEvent
    {
        glm::uvec2 size{};
    };

    struct KeyEvent
    {
        int scancode = 0;
        uint16_t key = 0;
        uint8_t mods = 0;
    };

    struct TextEvent
    {
        uint32_t code = 0;
    };

    struct MouseMoveEvent
    {
        glm::vec2 position{};
    };

    struct MouseButtonEvent
    {
        uint8_t button = 0;
        uint8_t mods = 0;
    };

    struct ScrollEvent
    {
        glm::vec2 offset{};
    };

    struct EmptyEvent
    {
    };

    enum class Type
    {
        None,

        Closed,
        Resized,
        KeyPressed,
        KeyReleased,
        TextEntered,
        MouseMoved,
        MouseButtonPressed,
        MouseButtonReleased,
        Scrolled
    };

    explicit Event()
        : type{Type::None}
    {
    }

    Type type = Type::None;

    union {
        EmptyEvent empty;
        SizeEvent size;                // Type::Resized
        KeyEvent key;                  // Type::KeyPressed, Type::KeyReleased
        TextEvent text;                // Type::TextEntered
        MouseMoveEvent mouseMove;      // Type::MouseMoved
        MouseButtonEvent mouseButton;  // Type::MouseButtonPressed, Type::MouseButtonReleased
        ScrollEvent scroll;            // Type::Scrolled
    };
};

}  // namespace core
