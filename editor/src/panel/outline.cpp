#include "sprpch.h"
#include "outline.h"

namespace spr {

    OutlinePanel::OutlinePanel() : Panel("Outline"), useSearchQuery(false)
    {
        searchQuery.reserve(64);
    }

    void OutlinePanel::Content() {
        ImGuiStyle& style = ImGui::GetStyle();

        ImGuiEx::VerticalSpace();
        ImGuiEx::HorizontalSpace();
        if (ImGuiEx::IconButton(0, ImGuiExIcon::Add))
            ImGui::OpenPopup("NewEntityPopup");
        ImGui::SameLine();

        Widgets::NewEntityPopup();

        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth() - ImGui::GetFrameHeight() - style.ItemSpacing.x * 2.0f);
        ImGui::InputText("##OutlineSearch", searchQuery.data(), searchQuery.capacity(), ImGuiInputTextFlags_EnterReturnsTrue);
        ImGui::SameLine();
        ImGuiEx::IconButton(0, ImGuiExIcon::Search);
        ImGui::Separator();

        Scene* scene = Scene::GetActiveScene();
        if (scene) {
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 5.0f, 2.0f });
            std::vector<Entity> entitiesToRemove;
            scene->GetRegistry().each([&](auto entityID) {
                Entity entity = { entityID, scene };
                EntityInfo& info = entity.GetComponent<EntityInfo>();
                ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
                bool selected = (!Selection::IsEmpty() && entityID == Selection::GetEntity().GetID());
                if (selected)
                    ImGui::PushStyleColor(ImGuiCol_Header, style.Colors[ImGuiCol_HeaderHovered]);

                bool open = ImGui::TreeNodeEx((void*)(uint64)entityID, treeFlags, info.name.data());
                bool removeEntity = false;
                if (ImGui::BeginPopupContextItem()) {
                    if (ImGui::MenuItem("Remove")) entitiesToRemove.push_back(entity);
                    ImGui::EndPopup();
                }
                if (open) {
                    scene->GetRegistry().visit(entityID, [&](const entt::type_info type) {
                        ImGui::Text(type.name().data());
                    });
                    ImGui::TreePop();
                }
                if (ImGui::IsItemClicked()) {
                    Selection::Set(entity);
                }

                if (selected)
                    ImGui::PopStyleColor();
            });
            ImGui::PopStyleVar();

            for (Entity& e : entitiesToRemove) scene->RemoveEntity(e);
            if(!entitiesToRemove.empty()) Selection::Clear();
        }
    }

}