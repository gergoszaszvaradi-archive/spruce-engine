#include "sprpch.h"
#include "ui.h"

namespace spr {

    UIContext UI::context;
    UIStyle UI::style;

    SPR_API void UI::Init(uint32 width, uint32 height)
    {
        Resize(width, height);
        context.texture = Renderer::GetWhiteTexture();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(Window::Get()->GetHandle(), true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    SPR_API void UI::Resize(uint32 width, uint32 height)
    {
        context.projection = Matrix4::Ortho(0, (float)width, 0, (float)height, -100.0f, 100.0f);
    }

    SPR_API void UI::Dispose()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    SPR_API void UI::BeginFrame()
    {
        Renderer::Begin(context.projection);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    SPR_API void UI::EndFrame()
    {
        Renderer::End();

        ImGuiIO& io = ImGui::GetIO();
        Sizeu size = Window::Get()->GetSize();
        io.DisplaySize = ImVec2((float)size.width, (float)size.height);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    SPR_API void UI::Rect(const Rectf& rect)
    {
        Renderer::SubmitQuad(0, rect, context.depth, { 0, 0, 1, 1 }, context.color, context.texture, context.shader);
    }

    SPR_API void UI::Text(const Rectf& rect, const std::wstring& text)
    {
        // TODO multiline text and wrapping
        float size = (float)context.font->GetSize();
        float ox = rect.x;
        float oy = rect.y + size - 4; // ! - 4 is temporary
        for (wchar c : text) {
            if (!context.font->HasCharacterInfo(c)) continue;
            const FontCharacter& ch = context.font->GetCharacterInfo(c);

            Renderer::SubmitQuad(0, { ox + ch.x, oy - ch.y, (float)ch.w, (float)ch.h }, context.depth, { ch.u0, ch.v0, ch.u1, ch.v1 }, context.color, context.font->GetAtlas().texture, context.shader);

            ox += ch.advance;
        }
    }

    SPR_API void UI::TextAligned(const Rectf& rect, const std::wstring& text, UITextAlignment hAlign, UITextAlignment vAlign)
    {
        Rectf r = rect;
        Sizef s = GetTextDimensions(text);
        if (hAlign == UITextAlignment::Center)
            r.x -= roundf(s.width * 0.5f);
        else if(hAlign == UITextAlignment::Right)
            r.x -= s.width;

        if (vAlign == UITextAlignment::Center)
            r.y -= roundf(s.height * 0.5f);
        else if (vAlign == UITextAlignment::Right)
            r.y -= s.height;

        Text(r, text);
    }

    SPR_API bool UI::Button(const Rectf& rect, const std::wstring& text)
    {
        context.color = style.buttonColor;
        Rect(rect);
        context.color = style.textColor;
        //Text(rect, text);
        TextAligned({rect.x + rect.width / 2, rect.y + rect.height / 2, rect.width, rect.height}, text, UITextAlignment::Center, UITextAlignment::Center);
        return false;
    }

    SPR_API void UI::Icon(const Rectf& rect, const Ref<UIIconSet>& iconSet, uint32 idx)
    {
        Renderer::SubmitQuad(0, rect, context.depth, iconSet->GetIconUV(idx), context.color, iconSet->GetTexture(), context.shader);
    }

    SPR_API Sizef UI::GetTextDimensions(const std::wstring& text)
    {
        Sizef s;
        for (wchar c : text) {
            if (!context.font->HasCharacterInfo(c)) continue;
            const FontCharacter& ch = context.font->GetCharacterInfo(c);

            s.width += ch.w;
            if(s.height < ch.h)
                s.height = ch.h;
        }
        return s;
    }

}