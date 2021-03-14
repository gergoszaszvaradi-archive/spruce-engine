#include "sprpch.h"
#include "window.h"

namespace spr {

    Window* Window::instance = nullptr;

    Window::Window(const WindowProps& props) : props(props) {
        ASSERT(instance == nullptr, "Multiple windows are not allowed!");
        instance = this;

        Graphics::Init();

        glfwWindowHint(GLFW_CENTER_CURSOR, true);
        glfwWindowHint(GLFW_RESIZABLE, props.resizable);
        glfwWindowHint(GLFW_VISIBLE, props.visible);
        glfwWindowHint(GLFW_DECORATED, !props.borderless);
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, props.focused);
        glfwWindowHint(GLFW_AUTO_ICONIFY, props.iconify);
        glfwWindowHint(GLFW_FLOATING, props.alwaysOnTop);
        glfwWindowHint(GLFW_MAXIMIZED, props.maximized);
        glfwWindowHint(GLFW_DOUBLEBUFFER, props.doubleBuffer);
        glfwWindowHint(GLFW_SAMPLES, 0);

        uint32 monitorCount = 0;
        GLFWmonitor* monitor = nullptr;
        if (props.fullscreen) {
            GLFWmonitor** monitors = glfwGetMonitors((int*)&monitorCount);
            if (props.monitor >= monitorCount)
                monitor = monitors[0];
            else
                monitor = monitors[props.monitor];

            const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);
            glfwWindowHint(GLFW_REFRESH_RATE, vidMode->refreshRate);
        }

        nativeWindow = glfwCreateWindow(props.size.width, props.size.height, props.title.c_str(), monitor, nullptr);
        glfwMakeContextCurrent(nativeWindow);
        glfwSetWindowUserPointer(nativeWindow, this);
        glfwSwapInterval(props.vSync);

        if (!props.maximized) {
            if (props.centerOnOpen) {
                if (monitor == nullptr)
                    monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);
                this->props.position.x = (vidMode->width - props.size.width) / 2;
                this->props.position.y = (vidMode->height - props.size.height) / 2;
            }
            glfwSetWindowPos(nativeWindow, this->props.position.x, this->props.position.y);
        }

        glfwSetWindowCloseCallback(nativeWindow, [](GLFWwindow* w) {
            Window* window = (Window*)glfwGetWindowUserPointer(w);
            if (window == nullptr) return;
            window->PushEvent(Event(EventType::WindowClosed));
        });
        glfwSetWindowPosCallback(nativeWindow, [](GLFWwindow* w, int x, int y) {
            Window* window = (Window*)glfwGetWindowUserPointer(w);
            Event e(EventType::WindowMoved);
            e.position.x = (uint32)x;
            e.position.y = (uint32)y;
            window->props.position.x = x;
            window->props.position.y = y;
            window->PushEvent(e);
        });
        glfwSetWindowSizeCallback(nativeWindow, [](GLFWwindow* w, int width, int height) {
            Window* window = (Window*)glfwGetWindowUserPointer(w);
            Event e(EventType::WindowResized);
            e.size.width = (uint32)width;
            e.size.height = (uint32)height;
            window->props.size.width = width;
            window->props.size.height = height;
            window->PushEvent(e);
        });
        glfwSetWindowFocusCallback(nativeWindow, [](GLFWwindow* w, int state) {
            Window* window = (Window*)glfwGetWindowUserPointer(w);
            Event e(EventType::WindowFocusChanged);
            e.state.value = (bool)state;
            window->PushEvent(e);
        });
        glfwSetKeyCallback(nativeWindow, [](GLFWwindow* w, int key, int scan, int action, int mods) {
            Window* window = (Window*)glfwGetWindowUserPointer(w);
            Event e(EventType::KeyPressed);
            e.keyboard.key = (KeyCode)key;
            e.keyboard.shift = mods & GLFW_MOD_SHIFT;
            e.keyboard.control = mods & GLFW_MOD_CONTROL;
            e.keyboard.alt = mods & GLFW_MOD_ALT;
            e.keyboard.capsLock = mods & GLFW_MOD_CAPS_LOCK;
            e.keyboard.numLock = mods & GLFW_MOD_NUM_LOCK;
            if (action == GLFW_REPEAT)
                e.type = EventType::KeyRepeated;
            else if (action == GLFW_RELEASE)
                e.type = EventType::KeyReleased;
            window->PushEvent(e);
        });
        glfwSetMouseButtonCallback(nativeWindow, [](GLFWwindow* w, int button, int action, int mods) {
            Window* window = (Window*)glfwGetWindowUserPointer(w);
            Event e(EventType::MousePressed);
            e.mouse.button = (MouseButton)button;
            e.mouse.shift = mods & GLFW_MOD_SHIFT;
            e.mouse.control = mods & GLFW_MOD_CONTROL;
            e.mouse.alt = mods & GLFW_MOD_ALT;
            e.mouse.capsLock = mods & GLFW_MOD_CAPS_LOCK;
            e.mouse.numLock = mods & GLFW_MOD_NUM_LOCK;
            if (action == GLFW_REPEAT)
                e.type = EventType::KeyRepeated;
            else if (action == GLFW_RELEASE)
                e.type = EventType::KeyReleased;
            window->PushEvent(e);
        });
        glfwSetCursorPosCallback(nativeWindow, [](GLFWwindow* w, double x, double y) {
            Window* window = (Window*)glfwGetWindowUserPointer(w);
            Event e(EventType::MouseMoved);
            e.position.x = (uint32)x;
            e.position.y = (uint32)y;
            window->PushEvent(e);
        });
        glfwSetScrollCallback(nativeWindow, [](GLFWwindow* w, double x, double y) {
            Window* window = (Window*)glfwGetWindowUserPointer(w);
            Event e(EventType::MouseScrolled);
            e.delta.x = (float)x;
            e.delta.y = (float)y;
            window->PushEvent(e);
        });
        glfwSetCursorEnterCallback(nativeWindow, [](GLFWwindow* w, int state) {
            Window* window = (Window*)glfwGetWindowUserPointer(w);
            Event e(EventType::MouseStateChanged);
            e.state.value = (bool)state;
            window->PushEvent(e);
        });

        uint32 w, h;
        glfwGetWindowSize(nativeWindow, (int*)&w, (int*)&h);

        Graphics::InitGL(w, h);
    }

    Window::~Window() {
        glfwDestroyWindow(nativeWindow);
    }

    SPR_API void Window::SetPosition(const Pointu& position)
    {
        props.position = position;
        glfwSetWindowPos(nativeWindow, (int)position.x, (int)position.y);
    }

    SPR_API void Window::SetSize(const Sizeu& size)
    {
        props.size = size;
        glfwSetWindowSize(nativeWindow, (int)size.width, (int)size.height);
    }

    SPR_API void Window::SetTitle(const std::string& title)
    {
        props.title = title;
        glfwSetWindowTitle(nativeWindow, title.c_str());
    }

    SPR_API void Window::BeginFrame()
    {
        glfwMakeContextCurrent(nativeWindow);
        spr::Graphics::Clear();
        spr::Graphics::SetViewport(0, 0, props.size.width, props.size.height);
    }

    SPR_API void Window::EndFrame()
    {
        glfwSwapBuffers(nativeWindow);
        glfwPollEvents();
    }

    SPR_API void Window::PushEvent(Event& e)
    {
        eventQueue.push(e);
    }

    SPR_API bool Window::PollEvent(Event& e)
    {
        if (eventQueue.empty())
            return false;
        e = eventQueue.front();
        eventQueue.pop();
        return true;
    }

    SPR_API Ref<Window> Window::Create(const WindowProps& props)
    {
        return CreateRef<Window>(props);
    }

}
