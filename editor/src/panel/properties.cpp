#include "sprpch.h"
#include "properties.h"

namespace spr {

    void PropertiesPanel::Content() {
        ImGuiStyle& style = ImGui::GetStyle();
        ImGuiEx::VerticalSpace();

        if (Selection::IsEmpty()) return;

        const Entity& entity = Selection::GetEntity();
        if (!entity) return;

        ImGui::BeginGroup();
        ImGuiEx::HorizontalSpace();

        EntityInfo& info = entity.GetComponent<EntityInfo>();

        ImGui::Checkbox("##Active", &info.active);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth() - ImGui::GetFrameHeight() - style.ItemSpacing.x * 2.0f);
        ImGui::InputText("##Name", info.name.data(), info.name.capacity(), ImGuiInputTextFlags_AutoSelectAll);
        ImGui::SameLine();
        if (ImGuiEx::IconButton(0, ImGuiExIcon::Add)) ImGui::OpenPopup("AddComponentOptions");

        if (ImGui::BeginPopup("AddComponentOptions")) {
            if (ImGui::MenuItem("Transform"))
                entity.TryAddComponent<Transform>();
            if (ImGui::MenuItem("SpriteRenderer"))
                entity.TryAddComponent<SpriteRenderer>();
            ImGui::EndPopup();
        }

        ImGui::EndGroup();

        DrawComponent<Transform>(entity);
        DrawComponent<SpriteRenderer>(entity);
    }

    template<>
    void PropertiesPanel::DrawComponentProperties<Transform>(const Entity& entity, Transform& transform)
    {
        ImGuiEx::DragVector3("Position", transform.position, 0.01f);
        Vector3D rotationInDegrees = { Math::ToDeg(transform.rotation.x), Math::ToDeg(transform.rotation.y), Math::ToDeg(transform.rotation.z) };
        ImGuiEx::DragVector3("Rotation", rotationInDegrees, 0.1f);
        transform.rotation = { Math::ToRad(rotationInDegrees.x), Math::ToRad(rotationInDegrees.y), Math::ToRad(rotationInDegrees.z) };
        ImGuiEx::DragVector3("Scale", transform.scale, 0.01f, 1.0f);
    }

    template<>
    void PropertiesPanel::DrawComponentProperties<SpriteRenderer>(const Entity& entity, SpriteRenderer& spriteRenderer)
    {
        ImGuiEx::ColorRGBA("Color", spriteRenderer.color);
        ImGuiEx::AssetInput<Shader>("Shader", spriteRenderer.shader);
        ImGuiEx::TextureInput("Texture", spriteRenderer.texture);
        if (spriteRenderer.texture && ImGui::Button("Scale to native size")) {
            Transform& transform = entity.GetComponent<Transform>();
            float r = (float)spriteRenderer.texture->GetWidth() / spriteRenderer.texture->GetHeight();
            transform.scale.x = transform.scale.y * r;
        }
    }

}