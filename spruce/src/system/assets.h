#pragma once
#include "core.h"

namespace spr {

    class Asset {
    public:
        //virtual bool LoadFromFile(const std::string& path) = 0;

        inline const std::string& GetName() const { return name; }

    protected:
        std::string name;
    };

    template<typename T>
    class AssetManager {
    public:
        SPR_API static Ref<T>& Get(const std::string& path);

    private:
        SPR_API static std::unordered_map<std::string, Ref<T>> assets;
    };

}