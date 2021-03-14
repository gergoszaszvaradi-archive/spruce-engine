#include "spruce.h"
#include "panel/properties.h"
#include "panel/scene.h"
#include "panel/outline.h"
#include "scene/scene.h"

#define SPR_EDITOR_VERSION "v0.0.1a"

namespace spr {

    class Editor : public spr::Application {
    public:
        std::vector<Ref<Panel>> panels;
        Ref<ScenePanel> scenePanel;

        Ref<Texture> testTexture;

        Ref<Scene> scene;

        void OnStart() override {
            SetEditor();
            ImGuiIO& io = ImGui::GetIO();

            io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/Rubik-Regular.ttf", 14.0f);
            io.ConfigWindowsMoveFromTitleBarOnly = true;
            io.ConfigWindowsResizeFromEdges = true;
            ImGui::StyleSpruce();
            ImGuiEx::Init();

            panels.push_back(CreateRef<PropertiesPanel>());
            scenePanel = CreateRef<ScenePanel>();
            panels.push_back(scenePanel);
            panels.push_back(CreateRef<OutlinePanel>());

            testTexture = Texture::Create("assets/textures/test.png");

            scene = Scene::Create();
        }

        void OnUpdate() override {
            scenePanel->OnUpdate();
        }

        void OnEvent(Event& e) override {
            scenePanel->OnEvent(e);
        }

        void BeginDockspace() {
            static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->GetWorkPos());
            ImGui::SetNextWindowSize(viewport->GetWorkSize());
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

            static bool dockspaceOpen = true;
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            ImGui::Begin("Dockspace", &dockspaceOpen, window_flags);
            ImGui::PopStyleVar();

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 5.0f, 5.0f });
            ImGui::PushStyleColor(ImGuiCol_MenuBarBg, {1, 0, 0, 1 });
            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    ImGui::MenuItem("New", "Ctrl+N");
                    if (ImGui::MenuItem("Quit", "Alt+F4")) Close();
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Window")) {
                    for (const Ref<Panel>& panel : panels) {
                        if (ImGui::MenuItem(panel->GetName().c_str())) {
                            panel->Show();
                        }
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Run")) {
                    if (ImGui::MenuItem("Launch")) {
                        // launch child process
                        std::system("..\\..\\example\\bin\\example.exe");
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            ImGui::PopStyleColor();
            ImGui::PopStyleVar();

            ImGuiID dockspace_id = ImGui::GetID("Dockspace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, viewport->Size.y - ImGui::GetFrameHeight() * 2.0f), dockspace_flags);
        }
        void EndDockspace() {
            ImGui::Separator();
            ImVec2 pos = { 0, ImGui::GetWindowHeight() - ImGui::GetFrameHeight() };
            ImGui::Text("Spruce " SPR_EDITOR_VERSION);
            ImGui::End();
        }

        void OnUI() override {
            BeginDockspace();

            for (const Ref<Panel>& panel : panels) {
                panel->Render();
            }

            ImGui::Begin("Console");
            ImGui::Text("asd");
            ImGui::End();

            ImGuiIO& io = ImGui::GetIO();
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 5.0f, 5.0f });
            ImGui::Begin("Stats", nullptr, ImGuiWindowFlags_NoCollapse);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGuiEx::VerticalSpace();
            ImGui::Text("Renderer:");
            const RendererStats& stats = Renderer::GetStats();
            ImGui::Text("Vertex Count: %u\nIndex Count: %u\nDraw Calls: %u", stats.vertexCount, stats.indexCount, stats.drawCalls);
            ImGui::End();
            ImGui::PopStyleVar();

            EndDockspace();
        }

    };

}

int main() {
    spr::WindowProps props;
    props.title = "Spruce " SPR_EDITOR_VERSION;
    props.size.width = 1600;
    props.size.height = 900;
    props.maximized = true;
    props.vSync = false;
    spr::CreateApplication<spr::Editor>(props);
}

#ifndef SPR_DEBUG
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    main();
    return 0;
}
#endif