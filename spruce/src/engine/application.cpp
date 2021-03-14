#include "sprpch.h"
#include "application.h"

namespace spr {

    Application* Application::instance = nullptr;

    Application::Application() : isEditor(false)
    {
        instance = this;
        state = ApplicationState::Initializing;
    }

    Application::~Application() {
        UI::Dispose();
        Graphics::Dispose();
        Lua::Dispose();
    }

    SPR_API void Application::Init(const WindowProps& props)
    {
        window = Window::Create(props);

        UI::Init(props.size.width, props.size.height);

        Lua::Init();
    }

    SPR_API void Application::Run()
    {
        if (state == ApplicationState::Stopping) return;

        state = ApplicationState::Running;
        while (state == ApplicationState::Running) {
            RunFrame();
        }
    }

    SPR_API void Application::RunFrame()
    {
        Event e;
        while (window->PollEvent(e)) {
            OnEvent(e);
            if (e.type == EventType::WindowClosed) {
                Close();
                return;
            }
        }

        window->BeginFrame();

        Renderer::BeginFrame();
        OnUpdate();
        Renderer::EndFrame();

        if (!isEditor) Renderer::RenderFrameBuffer();

        UI::BeginFrame();
        OnUI();
        UI::EndFrame();

        window->EndFrame();

        float time = (float)glfwGetTime();
        Time::deltaTime = time - Time::elapsedTime;
        Time::elapsedTime = time;
    }

    SPR_API void Application::Close()
    {
        state = ApplicationState::Stopping;
    }

    SPR_API void Application::SetEditor()
    {
        isEditor = true;
    }

}