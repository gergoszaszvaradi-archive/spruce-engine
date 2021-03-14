#pragma once
#include "core.h"
#include "scene/entity.h"

namespace spr {

    class Selection {
    public:
        static void Clear();
        static void Set(const Entity& entity);
        static void Add(const Entity& entity);

        inline static bool IsEmpty() { return entities.empty(); }
        inline static const Entity& GetEntity() { return entities[0]; }
        inline static const std::vector<Entity>& GetEntities() { return entities; }

    private:
        static std::vector<Entity> entities;
    };

}