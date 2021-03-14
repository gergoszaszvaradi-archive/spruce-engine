#pragma once
#include "core.h"

namespace spr {

    enum class KeyCode {
        None = -1,
        Space = 32,
        Apostrophe = 39,
        Comma = 44,
        Minus = 45,
        Period = 46,
        Slash = 47,
        Zero = 48,
        One = 49,
        Two = 50,
        Three = 51,
        Four = 52,
        Five = 53,
        Six = 54,
        Seven = 55,
        Eight = 56,
        Nine = 57,
        Semicolon = 59,
        Equal = 61,
        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,
        Left_bracket = 91,
        Backslash = 92,
        Right_bracket = 93,
        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Insert = 260,
        Del = 261,
        Right = 262,
        Left = 263,
        Down = 264,
        Up = 265,
        Page_up = 266,
        Page_down = 267,
        Home = 268,
        End = 269,
        Caps_lock = 280,
        Scroll_lock = 281,
        Num_lock = 282,
        Print_screen = 283,
        Pause = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,
        Num_1 = 320,
        Num_2 = 321,
        Num_3 = 322,
        Num_4 = 323,
        Num_5 = 324,
        Num_6 = 325,
        Num_7 = 326,
        Num_8 = 327,
        Num_9 = 328,
        Num_10 = 329,
        Num_decimal = 330,
        Num_devide = 331,
        Num_multiply = 332,
        Num_subtract = 333,
        Num_add = 334,
        Num_enter = 335,
        Num_equal = 336,
        Left_shift = 340,
        Left_control = 341,
        Left_alt = 342,
        Left_system = 343,
        Right_shift = 344,
        Right_control = 345,
        Right_alt = 346,
        Right_system = 347,
        Menu = 348
    };

    enum class MouseButton {
        None = -1,
        Left = 0,
        Right = 1,
        Middle = 2,
        Button1 = 0,
        Button2 = 1,
        Button3 = 2,
        Button4 = 3,
        Button5 = 4,
        Button6 = 5,
        Button7 = 6,
        Button8 = 7
    };

    enum class EventType {
        WindowClosed = 0,
        WindowMoved = BITFLAG(0),
        WindowResized = BITFLAG(1),
        WindowFocusChanged = BITFLAG(2),
        KeyPressed = BITFLAG(3),
        KeyRepeated = BITFLAG(4),
        KeyReleased = BITFLAG(5),
        MousePressed = BITFLAG(6),
        MouseReleased = BITFLAG(7),
        MouseMoved = BITFLAG(8),
        MouseScrolled = BITFLAG(9),
        MouseStateChanged = BITFLAG(10)
    };

    class Event {
    public:
        Event() : type(EventType::WindowClosed), size(), position(), delta(), state(), keyboard(), mouse() {};
        Event(EventType type) : type(type), size(), position(), delta(), state(), keyboard(), mouse() {};

    public:
        EventType type;

        struct SizeEvent {
            uint32 width, height;
        };

        struct PositionEvent {
            uint32 x, y;
        };

        struct DeltaEvent {
            float x, y;
        };

        struct StateEvent {
            bool value;
        };

        struct KeyEvent {
            KeyCode key;
            bool shift;
            bool control;
            bool alt;
            bool capsLock;
            bool numLock;
        };

        struct MouseEvent {
            MouseButton button;
            bool shift;
            bool control;
            bool alt;
            bool capsLock;
            bool numLock;
        };

        union
        {
            SizeEvent size;
            PositionEvent position;
            DeltaEvent delta;
            StateEvent state;
            KeyEvent keyboard;
            MouseEvent mouse;
        };
    };


    template<>
    inline std::string ToString<Event>(const Event& e) {
        switch (e.type)
        {
        case spr::EventType::WindowClosed:
            return "WindowClosed";
            break;
        case spr::EventType::WindowMoved:
            return "WindowMoved (x = " + std::to_string(e.position.x) + ", y = " + std::to_string(e.position.y) + ")";
            break;
        case spr::EventType::WindowResized:
            return "WindowResized (width = " + std::to_string(e.size.width) + ", height = " + std::to_string(e.size.height) + ")";
            break;
        case spr::EventType::WindowFocusChanged:
            return "WindowFocusChanged (state = " + std::to_string(e.state.value) + ")";
            break;
        case spr::EventType::KeyPressed:
            return "KeyPressed (key = " + std::to_string((int)e.keyboard.key) + ", char = " + (char)e.keyboard.key + ")";
            break;
        case spr::EventType::KeyRepeated:
            return "KeyRepeated (key = " + std::to_string((int)e.keyboard.key) + ", char = " + (char)e.keyboard.key + ")";
            break;
        case spr::EventType::KeyReleased:
            return "KeyReleased (key = " + std::to_string((int)e.keyboard.key) + ", char = " + (char)e.keyboard.key + ")";
            break;
        case spr::EventType::MousePressed:
            return "MousePressed (button = " + std::to_string((int)e.mouse.button) + ")";
            break;
        case spr::EventType::MouseReleased:
            return "MouseReleased (button = " + std::to_string((int)e.mouse.button) + ")";
            break;
        case spr::EventType::MouseMoved:
            return "MouseMoved (x = " + std::to_string(e.position.x) + ", y = " + std::to_string(e.position.y) + ")";
            break;
        case spr::EventType::MouseScrolled:
            return "MouseScrolled (deltaX = " + std::to_string(e.delta.x) + ", deltaY = " + std::to_string(e.delta.y) + ")";
            break;
        case spr::EventType::MouseStateChanged:
            return "MouseStateChanged (state = " + std::to_string(e.state.value) + ")";
            break;
        default:
            break;
        }
        return "";
    }

}