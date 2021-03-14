#pragma once
#include "core.h"
#include "graphics/texture.h"
#include "util/bounds.h"
#include "util/size.h"

namespace spr {

    class UIIconSet {
    public:
        SPR_API UIIconSet(const std::string& path, uint32 cols, uint32 rows);

        inline const Ref<Texture>& GetTexture() const { return texture; }
        inline Sizeu GetIconSize() const { return Sizeu(texture->GetWidth() / cols, texture->GetHeight() / rows); }
        SPR_API Boundsf GetIconUV(uint32 i) const;

        SPR_API static Ref<UIIconSet> Create(const std::string& path, uint32 cols, uint32 rows);

    private:
        Ref<Texture> texture;
        uint32 cols, rows;
    };

}