#pragma once

#include <GLFW/glfw3.h>

namespace core::keyboard
{
enum Key : uint16_t
{
    Space = GLFW_KEY_SPACE,
    Apostrophe = GLFW_KEY_APOSTROPHE,
    Comma = GLFW_KEY_COMMA,
    Minus = GLFW_KEY_MINUS,
    Period = GLFW_KEY_PERIOD,
    Slash = GLFW_KEY_SLASH,

    Number0 = GLFW_KEY_0,
    Number1 = GLFW_KEY_1,
    Number2 = GLFW_KEY_2,
    Number3 = GLFW_KEY_3,
    Number4 = GLFW_KEY_4,
    Number5 = GLFW_KEY_5,
    Number6 = GLFW_KEY_6,
    Number7 = GLFW_KEY_7,
    Number8 = GLFW_KEY_8,
    Number9 = GLFW_KEY_9,

    Semicolon = GLFW_KEY_SEMICOLON,
    Equal = GLFW_KEY_EQUAL,

    A = GLFW_KEY_A,
    B = GLFW_KEY_B,
    C = GLFW_KEY_C,
    D = GLFW_KEY_D,
    E = GLFW_KEY_E,
    F = GLFW_KEY_F,
    G = GLFW_KEY_G,
    H = GLFW_KEY_H,
    I = GLFW_KEY_I,
    J = GLFW_KEY_J,
    K = GLFW_KEY_K,
    L = GLFW_KEY_L,
    M = GLFW_KEY_M,
    N = GLFW_KEY_N,
    O = GLFW_KEY_O,
    P = GLFW_KEY_P,
    Q = GLFW_KEY_Q,
    R = GLFW_KEY_R,
    S = GLFW_KEY_S,
    T = GLFW_KEY_T,
    U = GLFW_KEY_U,
    V = GLFW_KEY_V,
    W = GLFW_KEY_W,
    X = GLFW_KEY_X,
    Y = GLFW_KEY_Y,
    Z = GLFW_KEY_Z,

    LeftBracked = GLFW_KEY_LEFT_BRACKET,
    RightBracked = GLFW_KEY_RIGHT_BRACKET,

    Escape = GLFW_KEY_ESCAPE,

    Enter = GLFW_KEY_ENTER,
    Tab = GLFW_KEY_TAB,
    Backspace = GLFW_KEY_BACKSPACE,
    Insert = GLFW_KEY_INSERT,
    Delete = GLFW_KEY_DELETE,

    Right = GLFW_KEY_RIGHT,
    Left = GLFW_KEY_LEFT,
    Down = GLFW_KEY_DOWN,
    Up = GLFW_KEY_UP,

    PageUp = GLFW_KEY_PAGE_UP,
    PageDown = GLFW_KEY_PAGE_DOWN,

    Home = GLFW_KEY_HOME,
    End = GLFW_KEY_END,

    F1 = GLFW_KEY_F1,
    F2 = GLFW_KEY_F2,
    F3 = GLFW_KEY_F3,
    F4 = GLFW_KEY_F4,
    F5 = GLFW_KEY_F5,
    F6 = GLFW_KEY_F6,
    F7 = GLFW_KEY_F7,
    F8 = GLFW_KEY_F8,
    F9 = GLFW_KEY_F9,
    F10 = GLFW_KEY_F10,
    F11 = GLFW_KEY_F11,
    F12 = GLFW_KEY_F12,

    Numpad0 = GLFW_KEY_KP_0,
    Numpad1 = GLFW_KEY_KP_1,
    Numpad2 = GLFW_KEY_KP_2,
    Numpad3 = GLFW_KEY_KP_3,
    Numpad4 = GLFW_KEY_KP_4,
    Numpad5 = GLFW_KEY_KP_5,
    Numpad6 = GLFW_KEY_KP_6,
    Numpad7 = GLFW_KEY_KP_7,
    Numpad8 = GLFW_KEY_KP_8,
    Numpad9 = GLFW_KEY_KP_9,

    NumpadDecimal = GLFW_KEY_KP_DECIMAL,
    NumpadDivide = GLFW_KEY_KP_DIVIDE,
    NumpadMultiply = GLFW_KEY_KP_MULTIPLY,
    NumpadSubstract = GLFW_KEY_KP_SUBTRACT,
    NumpadAdd = GLFW_KEY_KP_ADD,
    NumpadEnter = GLFW_KEY_KP_ENTER,
    NumpadEqual = GLFW_KEY_KP_EQUAL,

    LeftShift = GLFW_KEY_LEFT_SHIFT,
    LeftControl = GLFW_KEY_LEFT_CONTROL,
    LeftAlt = GLFW_KEY_LEFT_ALT,
    LeftSuper = GLFW_KEY_LEFT_SUPER,

    RightShift = GLFW_KEY_RIGHT_SHIFT,
    RightControl = GLFW_KEY_RIGHT_CONTROL,
    RightAlt = GLFW_KEY_RIGHT_ALT,
    RightSuper = GLFW_KEY_RIGHT_SUPER,

    Menu = GLFW_KEY_MENU,

    Last = GLFW_KEY_LAST
};

enum class Modifier : uint8_t
{
    Shift = 0x01,
    Control = 0x02,
    Alt = 0x04,
    Super = 0x08,
    CapsLock = 0x10,
    NumLock = 0x20,
};


uint8_t operator|(const Modifier &l, const Modifier &r);
bool operator&(const uint8_t &l, const Modifier &r);

}  // namespace core::keyboard
