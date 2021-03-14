#include "sprpch.h"
#include "scene.h"

#include "entity.h"

namespace spr {

    Scene* Scene::activeScene = nullptr;

    Scene::Scene()
    {
        SetActiveScene(this);
    }

    Scene::~Scene()
    {
    }

    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity = { registry.create(), this };
        entity.AddComponent<EntityInfo>(name);
        entity.AddComponent<Transform>();
        return entity;
    }

    void Scene::RemoveEntity(const Entity& entity)
    {
        registry.destroy(entity);
    }

    SPR_API void Scene::OnUpdate()
    {
        //Renderer::Begin(camera);
        auto group = registry.group<EntityInfo>(entt::get<Transform, SpriteRenderer>);
        for (auto entity : group) {
            auto [info, transform, renderer] = group.get<EntityInfo, Transform, SpriteRenderer>(entity);
            if (!info.active || !renderer.shader) continue;

            Matrix4 matrix = Matrix4::Translation(transform.position);

            if (transform.rotation.x != 0) matrix *= Matrix4::RotationX(transform.rotation.x);
            if (transform.rotation.y != 0) matrix *= Matrix4::RotationY(transform.rotation.y);
            if (transform.rotation.z != 0) matrix *= Matrix4::RotationZ(transform.rotation.z);

            matrix *= Matrix4::Scaled(transform.scale);

            Renderer::SubmitQuad((uint32)entity + 1, matrix, renderer.color, renderer.texture, renderer.shader);
        }
        //Renderer::End();
    }

    SPR_API Ref<Scene> Scene::Create()
    {
        return CreateRef<Scene>();
    }

    SPR_API void Scene::SetActiveScene(Scene* scene)
    {
        activeScene = scene;
    }

}