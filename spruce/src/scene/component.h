#pragma once
#include "core.h"
#include "system/assets.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "math/vector3D.h"
#include "math/vector4D.h"

#define SPR_REGISTER_COMPONENT(type) static const char* GetComponentName() { return #type; }

namespace spr {

    struct EntityInfo {
        SPR_REGISTER_COMPONENT(EntityInfo);

        std::string name;
        bool active;

        EntityInfo() : name("New Entity"), active(true) { this->name.reserve(64); };
        EntityInfo(const std::string& name) : name(name), active(true) { this->name.reserve(64); };
    };

    struct Transform {
        SPR_REGISTER_COMPONENT(Transform);

        Vector3D position;
        Vector3D rotation;
        Vector3D scale;

        Transform() : position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1) {};
    };

    struct SpriteRenderer {
        SPR_REGISTER_COMPONENT(SpriteRenderer);

        Vector4D color;
        Ref<Shader> shader;
        Ref<Texture> texture;

        SpriteRenderer() : color({ 1, 1, 1, 1 }) {};
        SpriteRenderer(const Ref<Shader>& shader) : color({ 1, 1, 1, 1 }), shader(shader) {};
        SpriteRenderer(const Vector4D& color, const Ref<Shader>& shader, const Ref<Texture>& texture) : color(color), shader(shader), texture(texture) {};
    };

}