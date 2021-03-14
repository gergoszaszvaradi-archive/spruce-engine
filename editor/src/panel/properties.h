#pragma once
#include "panel.h"
#include "outline.h"
#include "selection.h"
#include "imguiex.h"

namespace spr {

    class PropertiesPanel : public Panel {
    public:
        PropertiesPanel() : Panel("Properties") {}

        void Content() override;

        template<typename T>
        void DrawComponent(const Entity& entity) {
            ImGuiStyle& style = ImGui::GetStyle();

            if (!entity.HasComponent<T>()) return;

            ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
            float w = ImGui::GetContentRegionAvailWidth();
            bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeFlags, T::GetComponentName());
            bool removeComponent = false;
            ImGui::SameLine(w - ImGui::GetFrameHeight() - style.ItemSpacing.x);
            if (ImGuiEx::IconButton(0, ImGuiExIcon::More))
                ImGui::OpenPopup("ComponentSettings");

            if (ImGui::BeginPopup("ComponentSettings")) {
                if (ImGui::MenuItem("Remove")) {
                    removeComponent = true;
                }
                ImGui::EndPopup();
            }

            if (open) {
                T& component = entity.GetComponent<T>();
                DrawComponentProperties<T>(entity, component);
                ImGui::TreePop();
            }

            if(removeComponent)
                entity.RemoveComponent<T>();
        }

        template<typename T>
        void DrawComponentProperties(const Entity& entity, T& component) {};
    };

}