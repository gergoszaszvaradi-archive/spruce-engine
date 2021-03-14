#include "sprpch.h"
#include "panel.h"

namespace spr {

    Panel::Panel(const std::string& name, ImGuiWindowFlags flags) : name(name), visible(true), flags(ImGuiWindowFlags_NoCollapse | flags) {}

    void Panel::Show()
    {
        visible = true;
    }

    void Panel::Render()
    {
        if (!visible) return;

        ImGui::Begin(name.c_str(), &visible, flags);
        Content();
        ImGui::End();
    }

}