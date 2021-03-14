#pragma once
#include "core.h"
#include "event.h"
#include "util/point.h"
#include "util/size.h"

#include "graphics/graphics.h"

namespace spr {

    struct WindowProps {
        Pointu position;
        Sizeu size;
        uint32 monitor;
        bool centerOnOpen, resizable, visible, borderless, focused, iconify, alwaysOnTop, maximized, fullscreen, doubleBuffer, vSync;
        std::string title;

        WindowProps() : position(100, 100), size(1280, 720), monitor(0), centerOnOpen(true), resizable(true), visible(true), borderless(false), focused(true), iconify(true), alwaysOnTop(false), maximized(false), fullscreen(false), doubleBuffer(true), vSync(true), title("New Window") {};
        WindowProps(uint32 width, uint32 height, const std::string& title) : position(100, 100), size(width, height), monitor(0), centerOnOpen(true), resizable(true), visible(true), borderless(false), focused(true), iconify(true), alwaysOnTop(false), maximized(false), fullscreen(false), doubleBuffer(true), vSync(true), title(title) {};
    };

    class Window {
    public:
        SPR_API Window(const WindowProps& props);
        SPR_API ~Window();

        inline const WindowProps& GetProperties() const { return props; }
        inline GLFWwindow* GetHandle() const { return nativeWindow; }

        inline const Pointu& GetPosition() const { return props.position; }
        SPR_API void SetPosition(const Pointu& position);

        inline const Sizeu& GetSize() const { return props.size; }
        SPR_API void SetSize(const Sizeu& size);

        inline const std::string& GetTitle() const { return props.title; }
        SPR_API void SetTitle(const std::string& title);

        SPR_API void BeginFrame();
        SPR_API void EndFrame();

        SPR_API void PushEvent(Event& e);
        SPR_API bool PollEvent(Event& e);

        SPR_API static Ref<Window> Create(const WindowProps& props);
        inline static Window* Get() { return instance; }

    private:
        GLFWwindow* nativeWindow;
        WindowProps props;
        std::queue<Event> eventQueue;

        SPR_API static Window* instance;
    };

}