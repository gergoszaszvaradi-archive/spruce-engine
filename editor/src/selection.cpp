#include "sprpch.h"
#include "selection.h"

namespace spr {

    std::vector<Entity> Selection::entities;

    void Selection::Clear()
    {
        entities.clear();
    }

    void Selection::Set(const Entity& entity)
    {
        entities.clear();
        entities.push_back(entity);
    }

    void Selection::Add(const Entity& entity)
    {
        entities.push_back(entity);
    }

}