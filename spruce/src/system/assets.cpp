#include "sprpch.h"
#include "assets.h"

#include "graphics/texture.h"
#include "graphics/shader.h"

namespace spr {

    template<>
    std::unordered_map<std::string, Ref<Shader>> AssetManager<Shader>::assets;
    std::unordered_map<std::string, Ref<Texture>> AssetManager<Texture>::assets;

    template<>
    SPR_API static Ref<Shader>& AssetManager<Shader>::Get(const std::string& path)
    {
        auto it = assets.find(path);
        if (it == assets.end()) {
            Ref<Shader> shader = Shader::Create();
            shader->Bind();
            shader->LoadFromFile(path);
            return assets.emplace(path, shader).first->second;
        }
        return it->second;
    }

    template<>
    SPR_API static Ref<Texture>& AssetManager<Texture>::Get(const std::string& path)
    {
        auto it = assets.find(path);
        if (it == assets.end()) {
            Ref<Texture> texture = Texture::Create(path);
            return assets.emplace(path, texture).first->second;
        }
        return it->second;
    }

}