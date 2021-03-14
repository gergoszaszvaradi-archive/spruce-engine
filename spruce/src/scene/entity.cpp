#include "sprpch.h"
#include "entity.h"

namespace spr {

    Entity::Entity() : id(entt::null), scene(nullptr) {}

    Entity::Entity(Scene* scene) : id(entt::null), scene(scene) {}

    Entity::Entity(uint32 id, Scene* scene) : id((entt::entity)id), scene(scene) {}

    Entity::Entity(entt::entity entity, Scene* scene) : id(entity), scene(scene) {}

}