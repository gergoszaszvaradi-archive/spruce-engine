#include "sprpch.h"
#include "imguiex.h"

#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

namespace spr {

    Ref<UIIconSet> ImGuiEx::iconset;

    void ImGuiEx::Init()
    {
        iconset = UIIconSet::Create("assets/textures/iconset.png", 16, 16);
    }

    void ImGuiEx::HorizontalSpace(float space)
    {
        if (space == 0.0f) space = ImGui::GetStyle().ItemSpacing.x;
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + space);
    }

    void ImGuiEx::VerticalSpace(float space)
    {
        if (space == 0.0f) space = ImGui::GetStyle().ItemSpacing.x;
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + space);
    }

    bool ImGuiEx::ColoredButton(const char* label, const ImVec4& color, const ImVec4& hoverColor, const ImVec2& size)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, color);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, hoverColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);
        bool pressed = ImGui::Button(label, size);
        ImGui::PopStyleColor(3);
        return pressed;
    }

    void ImGuiEx::DragVector2(const char* label, Vector2D& v, float speed, float resetValue, float columnWidth)
    {
        ImGuiStyle& style = ImGui::GetStyle();

        ImGui::PushID((int)&v);

        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
        ImGui::Columns(2, 0, false);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::AlignTextToFramePadding();
        ImGui::Text(label);
        ImGui::NextColumn();

        float s = (ImGui::GetContentRegionAvailWidth() - style.ItemSpacing.x) / 2.0f;
        float buttonSize = ImGui::GetFrameHeight();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
        ImGui::BeginGroup();
        if (ColoredButton("X", { 0.98431f, 0.35686f, 0.35686f, 1.0f }, { 1.0f, 0.45686f, 0.45686f, 1.0f }, { buttonSize, buttonSize }))
            v.x = resetValue;
        ImGui::SameLine();
        ImGui::PushItemWidth(s - buttonSize);
        ImGui::DragFloat("##X", &v.x, speed);
        ImGui::PopItemWidth();
        ImGui::EndGroup();
        ImGui::PopStyleVar();

        ImGui::SameLine();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
        ImGui::BeginGroup();
        if (ColoredButton("Y", { 0.42352f, 0.75686f, 0.15686f, 1.0f }, { 0.52352f, 0.85686f, 0.25686f, 1.0f }, { buttonSize, buttonSize }))
            v.y = resetValue;
        ImGui::SameLine();
        ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth() - style.ItemInnerSpacing.x);
        ImGui::DragFloat("##Y", &v.y, speed);
        ImGui::PopItemWidth();
        ImGui::EndGroup();
        ImGui::PopStyleVar();

        ImGui::Columns(1);
        ImGui::PopStyleVar();

        ImGui::PopID();
    }

    void ImGuiEx::DragVector3(const char* label, spr::Vector3D& v, float speed, float resetValue, float columnWidth)
    {
        ImGuiStyle& style = ImGui::GetStyle();

        ImGui::PushID((int)&v);

        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
        ImGui::Columns(2, 0, false);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::AlignTextToFramePadding();
        ImGui::Text(label);
        ImGui::NextColumn();

        float s = (ImGui::GetContentRegionAvailWidth() - style.ItemSpacing.x * 2.0f) / 3.0f;
        float buttonSize = ImGui::GetFrameHeight();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
        ImGui::BeginGroup();
        if (ColoredButton("X", { 0.98431f, 0.35686f, 0.35686f, 1.0f }, { 1.0f, 0.45686f, 0.45686f, 1.0f }, { buttonSize, buttonSize }))
            v.x = resetValue;
        ImGui::SameLine();
        ImGui::PushItemWidth(s - buttonSize);
        ImGui::DragFloat("##X", &v.x, speed);
        ImGui::PopItemWidth();
        ImGui::EndGroup();
        ImGui::PopStyleVar();

        ImGui::SameLine();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
        ImGui::BeginGroup();
        if (ColoredButton("Y", { 0.42352f, 0.75686f, 0.15686f, 1.0f }, { 0.52352f, 0.85686f, 0.25686f, 1.0f }, { buttonSize, buttonSize }))
            v.y = resetValue;
        ImGui::SameLine();
        ImGui::PushItemWidth(s - buttonSize);
        ImGui::DragFloat("##Y", &v.y, speed);
        ImGui::PopItemWidth();
        ImGui::EndGroup();
        ImGui::PopStyleVar();

        ImGui::SameLine();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
        ImGui::BeginGroup();
        if (ColoredButton("Z", { 0.07058f, 0.40784f, 0.90980f, 1.0f }, { 0.17058f, 0.50784f, 1.0f, 1.0f }, { buttonSize, buttonSize }))
            v.z = resetValue;
        ImGui::SameLine();
        ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth() - style.ItemInnerSpacing.x);
        ImGui::DragFloat("##Z", &v.z, speed);
        ImGui::PopItemWidth();
        ImGui::EndGroup();
        ImGui::PopStyleVar();

        ImGui::Columns(1);
        ImGui::PopStyleVar();

        ImGui::PopID();
    }

    void ImGuiEx::DragVector4(const char* label, Vector4D& v, float speed, float resetValue, float columnWidth)
    {
        ImGuiStyle& style = ImGui::GetStyle();

        ImGui::PushID((int)&v);

        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
        ImGui::Columns(2, 0, false);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::AlignTextToFramePadding();
        ImGui::Text(label);
        ImGui::NextColumn();

        float s = (ImGui::GetContentRegionAvailWidth() - style.ItemSpacing.x * 3.0f) / 4.0f;
        float buttonSize = ImGui::GetFrameHeight();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
        ImGui::BeginGroup();
        if (ColoredButton("X", { 0.98431f, 0.35686f, 0.35686f, 1.0f }, { 1.0f, 0.45686f, 0.45686f, 1.0f }, { buttonSize, buttonSize }))
            v.x = resetValue;
        ImGui::SameLine();
        ImGui::PushItemWidth(s - buttonSize);
        ImGui::DragFloat("##X", &v.x, speed);
        ImGui::PopItemWidth();
        ImGui::EndGroup();
        ImGui::PopStyleVar();

        ImGui::SameLine();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
        ImGui::BeginGroup();
        if (ColoredButton("Y", { 0.42352f, 0.75686f, 0.15686f, 1.0f }, { 0.52352f, 0.85686f, 0.25686f, 1.0f }, { buttonSize, buttonSize }))
            v.y = resetValue;
        ImGui::SameLine();
        ImGui::PushItemWidth(s - buttonSize);
        ImGui::DragFloat("##Y", &v.y, speed);
        ImGui::PopItemWidth();
        ImGui::EndGroup();
        ImGui::PopStyleVar();

        ImGui::SameLine();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
        ImGui::BeginGroup();
        if (ColoredButton("Z", { 0.07058f, 0.40784f, 0.90980f, 1.0f }, { 0.17058f, 0.50784f, 1.0f, 1.0f }, { buttonSize, buttonSize }))
            v.z = resetValue;
        ImGui::SameLine();
        ImGui::PushItemWidth(s - buttonSize);
        ImGui::DragFloat("##Z", &v.z, speed);
        ImGui::PopItemWidth();
        ImGui::EndGroup();
        ImGui::PopStyleVar();

        ImGui::SameLine();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
        ImGui::BeginGroup();
        if (ColoredButton("W", { 0.5f, 0.5f, 0.5f, 1.0f }, { 0.6f, 0.6f, 0.6f, 1.0f }, { buttonSize, buttonSize }))
            v.w = resetValue;
        ImGui::SameLine();
        ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth() - style.ItemInnerSpacing.x);
        ImGui::DragFloat("##W", &v.w, speed);
        ImGui::PopItemWidth();
        ImGui::EndGroup();
        ImGui::PopStyleVar();

        ImGui::Columns(1);
        ImGui::PopStyleVar();

        ImGui::PopID();
    }

    void ImGuiEx::ColorRGBA(const char* label, Vector4D& c, float columnWidth)
    {
        ImGuiStyle& style = ImGui::GetStyle();

        ImGui::PushID((int)&c);

        ImGui::Columns(2, 0, false);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::AlignTextToFramePadding();
        ImGui::Text(label);
        ImGui::NextColumn();

        if (ImGui::ColorButton("##ColorButton", { c.x, c.y, c.z, c.w })) {
            ImGui::OpenPopup("ColorPicker");
        }

        if (ImGui::BeginPopup("ColorPicker")) {
            VerticalSpace();
            HorizontalSpace();
            ImGui::PushStyleColor(ImGuiCol_FrameBg, style.Colors[ImGuiCol_WindowBg]);
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, style.Colors[ImGuiCol_WindowBg]);
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, style.Colors[ImGuiCol_WindowBg]);
            ImGui::ColorPicker4("##Picker", &c.x);
            ImGui::PopStyleColor(3);
            ImGui::SameLine();
            ImGui::Dummy({ 0, 0 });
            VerticalSpace();
            ImGui::EndPopup();
        }

        ImGui::SameLine();
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth() - style.ItemSpacing.x);
        ImGui::ColorEdit4("##Color", &c.x, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);

        ImGui::Columns(1);

        ImGui::PopID();
    }

    bool ImGuiEx::IconButton(int id, ImGuiExIcon icon, ImVec4 bgColor, float iconSize)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImGui::PushID(id + (int)icon);
        ImGui::PushStyleColor(ImGuiCol_Button, bgColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, style.Colors[ImGuiCol_TextSelectedBg]);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, style.Colors[ImGuiCol_TextSelectedBg]);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 5, 5 });
        if (iconSize == 0.0f)
            iconSize = iconset->GetIconSize().width;
        Boundsf uv = iconset->GetIconUV((uint32)icon);
        bool pressed = ImGui::ImageButton((ImTextureID)iconset->GetTexture()->GetID(), { iconSize, iconSize }, { uv.x1, uv.y1 }, { uv.x2, uv.y2 });
        ImGui::PopStyleColor(3);
        ImGui::PopStyleVar();
        ImGui::PopID();
        return pressed;
    }

    bool ImGuiEx::TextureInput(const char* label, Ref<Texture>& texture, float columnWidth)
    {
        ImGuiStyle& style = ImGui::GetStyle();

        uint64 id = (uint64)label[0] + (uint64)&(*texture);
        ImGui::PushID(id);

        ImGui::Columns(2, 0, false);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::AlignTextToFramePadding();
        ImGui::Text(label);
        ImGui::NextColumn();

        if (texture) {
            float r = texture->GetWidth() / texture->GetHeight();
            float s = ImGui::GetFrameHeight() / ((r >= 1) ? texture->GetWidth() : texture->GetHeight());

            float w = texture->GetWidth() * s;
            float h = texture->GetHeight() * s;
            ImGui::Image((ImTextureID)texture->GetID(), { w, h });
            ImGui::SameLine(0.0f, ((w < ImGui::GetFrameHeight()) ? ImGui::GetFrameHeight() - w : 0.0f) + style.ItemSpacing.x);
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth() - ImGui::GetFrameHeight() - style.ItemSpacing.x * 2.0f);
            ImGui::InputText("##ResourceFile", (char*)texture->GetName().data(), texture->GetName().size(), ImGuiInputTextFlags_ReadOnly);
        }
        else {
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth() - ImGui::GetFrameHeight() - style.ItemSpacing.x * 2.0f);
            ImGui::InputText("##ResourceFile", "", 0, ImGuiInputTextFlags_ReadOnly);
        }
        ImGui::SameLine();
        if (ImGuiEx::IconButton(id, ImGuiExIcon::Browse)) {
            std::string path = OpenFileDialog();
            if (!path.empty()) {
                texture = AssetManager<Texture>::Get(path);
            }
        }
        //ImGui::SameLine();
        //if (ImGuiEx::IconButton(ImGuiExIcon::Settings))
        //    ImGui::OpenPopup("ResourceSettings");

        //if (ImGui::BeginPopup("ResourceSettings")) {
        //    ResourceSettings<Texture>(texture);
        //    ImGui::EndPopup();
        //}

        ImGui::Columns(1);
        ImGui::PopID();
        return true;
    }

    std::string ImGuiEx::OpenFileDialog(const std::string& extension, const std::string& description)
    {
#ifdef SPR_WINDOWS
        OPENFILENAMEA ofn;
        CHAR szFile[256] = { 0 };
        std::string filter = std::string(description + "\0" + extension + "\0");
        ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
        ofn.lStructSize = sizeof(OPENFILENAMEA);
        ofn.hwndOwner = glfwGetWin32Window(glfwGetCurrentContext());
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = filter.data();
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetOpenFileNameA(&ofn) == TRUE) {
            return ofn.lpstrFile;
        }
        return "";
#else
        ASSERT(true, "File dialogs are not implemented on this operating system!");
#endif
    }

    std::string ImGuiEx::SaveFileDialog(const std::string& extension, const std::string& description)
    {
#ifdef SPR_WINDOWS
        OPENFILENAMEA ofn;
        CHAR szFile[256] = { 0 };
        std::string filter = std::string(description + "\0" + extension + "\0");
        ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
        ofn.lStructSize = sizeof(OPENFILENAMEA);
        ofn.hwndOwner = glfwGetWin32Window(glfwGetCurrentContext());
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = filter.data();
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetSaveFileNameA(&ofn) == TRUE) {
            return ofn.lpstrFile;
        }
        return "";
#else
        ASSERT(true, "File dialogs are not implemented on this operating system!");
#endif
    }

}