#include "sprpch.h"
#include "iconset.h"

namespace spr {

    UIIconSet::UIIconSet(const std::string& path, uint32 cols, uint32 rows) : cols(cols), rows(rows)
    {
        texture = Texture::Create(path);
    }

    SPR_API Boundsf UIIconSet::GetIconUV(uint32 i) const
    {
        uint32 x = i % cols;
        uint32 y = i / cols;
        return {
            (1.0f / cols) * x,
            (1.0f / rows) * y,
            (1.0f / cols) * (x+1),
            (1.0f / rows) * (y+1)
        };
    }

    SPR_API Ref<UIIconSet> UIIconSet::Create(const std::string& path, uint32 cols, uint32 rows)
    {
        return CreateRef<UIIconSet>(path, cols, rows);
    }

}