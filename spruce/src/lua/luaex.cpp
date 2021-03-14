#include "sprpch.h"
#include "luaex.h"

#include "util/point.h"
#include "math/vector3D.h"

#include "scene/scene.h"
#include "scene/entity.h"

namespace spr {

    lua_State* Lua::L = nullptr;

    SPR_API void Lua::LoadDefinitions()
    {
        LuaClass<Pointi>("Pointi")
            .AddConstructor<int, int>()
            .AddProperty<int>("x", &Pointi::x)
            .AddProperty<int>("y", &Pointi::y);

        LuaClass<Pointu>("Pointu")
            .AddConstructor<uint32, uint32>()
            .AddProperty<uint32>("x", &Pointu::x)
            .AddProperty<uint32>("y", &Pointu::y);

        LuaClass<Pointf>("Pointf")
            .AddConstructor<float, float>()
            .AddProperty<float>("x", &Pointf::x)
            .AddProperty<float>("y", &Pointf::y);

        LuaClass<Pointd>("Pointd")
            .AddConstructor<double, double>()
            .AddProperty<double>("x", &Pointd::x)
            .AddProperty<double>("y", &Pointd::y);


        LuaClass<Vector2D>("Vector2D")
            .AddConstructor<float, float>()
            .AddProperty<float>("x", &Vector2D::x)
            .AddProperty<float>("y", &Vector2D::y)
            .AddFunction<float>("Length", &Vector2D::Length)
            .AddFunction<float>("SqLength", &Vector2D::SqLength)
            .AddFunction<Vector2D>("Normalized", &Vector2D::Normalized)
            .AddFunction<void>("Normalize", &Vector2D::Normalize);

        LuaClass<Vector3D>("Vector3D")
            .AddConstructor<float, float, float>()
            .AddProperty<float>("x", &Vector3D::x)
            .AddProperty<float>("y", &Vector3D::y)
            .AddProperty<float>("z", &Vector3D::z)
            .AddFunction<float>("Length", &Vector3D::Length)
            .AddFunction<float>("SqLength", &Vector3D::SqLength)
            .AddFunction<Vector3D>("Normalized", &Vector3D::Normalized)
            .AddFunction<void>("Normalize", &Vector3D::Normalize);


        LuaClass<Entity>("Entity")
            .AddConstructor<>();


        LuaClass<Scene>("Scene")
            .AddConstructor<>()
            .AddDestructor()
            .AddFunction<Entity, const std::string&>("CreateEntity", &Scene::CreateEntity)
            .AddFunction<void, const Entity&>("RemoveEntity", &Scene::RemoveEntity);
    }

}