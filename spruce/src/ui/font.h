#pragma once
#include "core.h"
#include "math/math.h"
#include "graphics/texture.h"
#include "graphics/mesh.h"

#define SPR_USE_FREETYPE

#ifdef SPR_USE_FREETYPE
#include "freetype/config/ftheader.h"
#include "freetype/freetype.h"
#else
#include "STB/stb_rect_pack.h"
#include "STB/stb_truetype.h"
#endif

namespace spr {

    struct FontCharacter {
        float u0, v0, u1, v1;
        float x, y, w, h;
        float advance;
    };

    struct FontAtlas {
        Ref<Texture> texture;
        int padding = 1;
        float oversampleH = 1, oversampleV = 1;
    };

    class Font {
    public:
        SPR_API Font(const std::string& path, uint32 size = 48);
        SPR_API ~Font();

        inline bool HasCharacterInfo(wchar c) const { return characters.find(c) != characters.end(); }
        inline const FontCharacter& GetCharacterInfo(wchar c) const { return characters.at(c); }
        inline uint32 GetSize() const { return size; }
        inline const FontAtlas& GetAtlas() const { return atlas; }

        SPR_API static Ref<Font> Create(const std::string& path, uint32 size = 48);

    private:
        FontAtlas atlas;
        uint32 size;
        std::unordered_map<wchar, FontCharacter> characters;
    };

}