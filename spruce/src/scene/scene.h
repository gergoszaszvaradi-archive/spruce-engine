#pragma once
#include "core.h"
#include "entt/entt.hpp"
#include "component.h"
#include "graphics/renderer.h"

namespace spr {

    class Entity;

    class Scene {
    public:
        SPR_API Scene();
        SPR_API ~Scene();

        Entity CreateEntity(const std::string& name = "New Entity");
        void RemoveEntity(const Entity& entity);
        
        SPR_API void OnUpdate();

        inline entt::registry& GetRegistry() { return registry; }

        SPR_API static Ref<Scene> Create();
        inline static Scene* GetActiveScene() { return activeScene; }
        SPR_API static void SetActiveScene(Scene* scene);
    private:
        entt::registry registry;

        SPR_API static Scene* activeScene;

        friend class Entity;
    };

}