#pragma once
#include "core.h"
#include "window.h"
#include "ui/ui.h"
#include "system/time.h"
#include "lua/luaex.h"

namespace spr {

    enum class ApplicationState {
        Initializing,
        Running,
        Stopping
    };

    class Application {
    public:
        SPR_API Application();
        SPR_API ~Application();

        virtual void OnStart() {};
        virtual void OnEvent(Event& e) {};
        virtual void OnUpdate() {};
        virtual void OnUI() {};
        virtual void OnPreRender() {};
        virtual void OnPostRender() {};
        virtual void OnClose() {};

        SPR_API void Init(const WindowProps& props);
        SPR_API void Run();
        SPR_API void RunFrame();
        SPR_API void Close();

        inline bool IsEditor() const { return isEditor; }
        SPR_API void SetEditor();

    private:
        bool isEditor;
        Ref<Window> window;
        ApplicationState state;
        static Application* instance;
    };

    template<typename T>
    void CreateApplication(const WindowProps& props) {
        T* app = new T();
        app->Init(props);
        app->OnStart();
        app->Run();
        app->OnClose();
        delete app;
    }
}