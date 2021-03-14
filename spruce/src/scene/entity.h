#pragma once
#include "core.h"
#include "scene.h"
#include "entt/entt.hpp"

namespace spr {

    class Entity {
    public:
        SPR_API Entity();
        SPR_API Entity(Scene* scene);
        SPR_API Entity(uint32 id, Scene* scene);
        SPR_API Entity(entt::entity id, Scene* scene);

        template<typename T, typename ... Args>
        T& AddComponent(Args&& ... args) const {
            ASSERT(!HasComponent<T>(), "Entity already has component!");
            return scene->registry.emplace<T>(id, std::forward<Args>(args)...);
        }

        template<typename T, typename ... Args>
        T& TryAddComponent(Args&& ... args) const {
            if (HasComponent<T>())
                return GetComponent<T>();
            return scene->registry.emplace<T>(id, std::forward<Args>(args)...);
        }

        template<typename T>
        T& GetComponent() const {
            ASSERT(HasComponent<T>(), "Entity does not have component!")
            return scene->registry.get<T>(id);
        }

        template<typename T>
        void RemoveComponent() const {
            ASSERT(HasComponent<T>(), "Entity does not have component!")
            scene->registry.remove<T>(id);
        }

        template<typename T>
        bool HasComponent() const {
            return scene->registry.has<T>(id);
        }

        operator bool() const { return scene != nullptr && scene->registry.valid(id); }
        operator entt::entity() const { return id; }
        inline const entt::entity& GetID() const { return id; }

        bool operator == (const Entity& other) const { return id == other.id && scene == other.scene; }
        bool operator != (const Entity& other) const { return !(*this == other); }

    private:
        entt::entity id;
        Scene* scene;
    };

}