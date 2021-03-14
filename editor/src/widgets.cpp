#include "sprpch.h"
#include "widgets.h"

namespace spr {

    void Widgets::NewEntityPopup(const Vector3D& newEntityPosition)
    {
        if (ImGui::BeginPopup("NewEntityPopup")) {
            if (ImGui::MenuItem("Empty Entity")) {
                Entity entity = Scene::GetActiveScene()->CreateEntity();
                entity.GetComponent<Transform>().position = newEntityPosition;
                Selection::Set(entity);
            }
            if (ImGui::MenuItem("Sprite")) {
                Entity entity = Scene::GetActiveScene()->CreateEntity();
                entity.GetComponent<Transform>().position = newEntityPosition;
                entity.AddComponent<SpriteRenderer>(AssetManager<Shader>::Get("assets/shaders/default.glsl"));
                Selection::Set(entity);
            }
            ImGui::EndPopup();
        }
    }

}