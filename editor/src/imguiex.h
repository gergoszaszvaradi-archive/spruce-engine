#pragma once
#include "imgui.h"
#include "math/vector2D.h"
#include "math/vector3D.h"
#include "math/vector4D.h"
#include "ui/iconset.h"
#include "system/assets.h"
#include "imgui_internal.h"

namespace spr {

    enum class ImGuiExIcon {
        ArrowDown = 0,
        Add,
        More,
        Hand,
        Move,
        Rotate,
        Scale,
        Search,
        Browse,
        Settings,
        Global,
        ThreeD
    };

    class ImGuiEx {
    public:
        static void Init();

        static void HorizontalSpace(float space = 0.0f);
        static void VerticalSpace(float space = 0.0f);

        static bool ColoredButton(const char* label, const ImVec4& color, const ImVec4& hoverColor, const ImVec2& size = ImVec2(0, 0));

        static void DragVector2(const char* label, Vector2D& v, float speed = 0.01f, float resetValue = 0.0f, float columnWidth = 100.0f);
        static void DragVector3(const char* label, Vector3D& v, float speed = 0.01f, float resetValue = 0.0f, float columnWidth = 100.0f);
        static void DragVector4(const char* label, Vector4D& v, float speed = 0.01f, float resetValue = 0.0f, float columnWidth = 100.0f);

        static void ColorRGBA(const char* label, Vector4D& c, float columnWidth = 100.0f);

        static bool IconButton(int id, ImGuiExIcon icon, ImVec4 bgColor = { 0, 0, 0, 0 }, float iconSize = 0.0f);

        template<typename T>
        static bool AssetInput(const char* label, Ref<T>& asset, float columnWidth = 100.0f) {
            ImGuiStyle& style = ImGui::GetStyle();

            uint64 id = (uint64)label[0] + (uint64)&(*asset);
            ImGui::PushID(id);

            ImGui::Columns(2, 0, false);
            ImGui::SetColumnWidth(0, columnWidth);
            ImGui::AlignTextToFramePadding();
            ImGui::Text(label);
            ImGui::NextColumn();

            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth() - ImGui::GetFrameHeight() - style.ItemSpacing.x * 2.0f);
            if (asset) {
                ImGui::InputText("##ResourceFile", (char*)asset->GetName().c_str(), asset->GetName().size(), ImGuiInputTextFlags_ReadOnly);
            }
            else {
                ImGui::InputText("##ResourceFile", "", 0, ImGuiInputTextFlags_ReadOnly);
            }
            ImGui::SameLine();
            if (ImGuiEx::IconButton(id, ImGuiExIcon::Browse)) {
                std::string path = OpenFileDialog();
                if (!path.empty()) {
                    asset = AssetManager<T>::Get(path);
                }
            }

            ImGui::Columns(1);
            ImGui::PopID();
            return true;
        }


        static bool TextureInput(const char* label, Ref<Texture>& texture, float columnWidth = 100.0f);

        static std::string OpenFileDialog(const std::string& extension = "", const std::string& description = "");
        static std::string SaveFileDialog(const std::string& extension = "", const std::string& description = "");

    public:
        static Ref<UIIconSet> iconset;
    };

}