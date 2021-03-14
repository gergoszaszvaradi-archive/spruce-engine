#include "sprpch.h"
#include "font.h"

namespace spr {

    Font::Font(const std::string& path, uint32 size)
    {
        this->size = size;

#ifdef SPR_USE_FREETYPE
        FT_Library library;
        FT_Face face;

        ASSERT(FT_Init_FreeType(&library) == FT_Err_Ok, "Error loading in FreeType!");
        ASSERT(FT_New_Face(library, path.c_str(), 0, &face) == FT_Err_Ok, "Unkown font file format!");

        FT_Set_Char_Size(face, size << 6, size << 6, 72, 72);

        uint32 textureWidth = 0, textureHeight = 0;
        std::vector<int> codepoints;

        for (int c = 32; c < 255; c++) {
            uint32 glyph = FT_Get_Char_Index(face, c);
            if (glyph == 0) continue;
            codepoints.push_back(c);

            FT_Load_Glyph(face, glyph, FT_LOAD_RENDER);
            textureWidth += (face->glyph->metrics.width >> 6) + atlas.padding;
            if (textureHeight < (uint32)(face->glyph->metrics.height >> 6) + atlas.padding)
                textureHeight = (uint32)(face->glyph->metrics.height >> 6) + atlas.padding;
        }

        uchar* bitmap = new uchar[(uint64)textureWidth * (uint64)textureHeight * 4];

        uint32 x = 0;
        for (int c : codepoints) {
            FT_Load_Char(face, c, FT_LOAD_RENDER);
            FT_Bitmap* bmp = &face->glyph->bitmap;
            for (uint32 i = 0; i < bmp->rows; i++) {
                for (uint32 j = 0; j < bmp->width; j++) {
                    bitmap[i * textureWidth * 4 + (x + j) * 4 + 0] = 255;
                    bitmap[i * textureWidth * 4 + (x + j) * 4 + 1] = 255;
                    bitmap[i * textureWidth * 4 + (x + j) * 4 + 2] = 255;
                    bitmap[i * textureWidth * 4 + (x + j) * 4 + 3] = bmp->buffer[i * bmp->pitch + j];
                }
            }

            characters.insert(std::make_pair<wchar, FontCharacter>((wchar)c, {
                x / (float)textureWidth, 0.0f, (x + bmp->width) / (float)textureWidth, bmp->rows / (float)textureHeight,
                (float)(face->glyph->metrics.horiBearingX >> 6), (float)(face->glyph->metrics.horiBearingY >> 6), (float)(bmp->width), (float)(bmp->rows),
                (float)(face->glyph->metrics.horiAdvance >> 6)
                }));

            if (bmp != nullptr)
                x += bmp->width + atlas.padding;
        }

        atlas.texture = Texture::Create(textureWidth, textureHeight, TextureInternalFormat::RGBA);
        atlas.texture->Bind();
        atlas.texture->SetData(bitmap, TextureDataFormat::RGBA);

        FT_Done_FreeType(library);
#else
        std::basic_fstream<uchar> file(path, std::ios::in | std::ios::binary | std::ios::ate);
        ASSERT(file.is_open(), "File", path, "does not exist!");
        int len = (int)file.tellg();
        file.seekg(0, std::ios::beg);
        uchar* data = new uchar[len];
        file.read(data, len);
        file.close();

        uint32 bitmapWidth = 0;
        uint32 bitmapHeight = 0;

        int fontOffset = stbtt_GetFontOffsetForIndex(data, 0);
        stbtt_fontinfo fontInfo;
        ASSERT(stbtt_InitFont(&fontInfo, data, fontOffset), "Failed to init font!");

        float scale = stbtt_ScaleForPixelHeight(&fontInfo, (float)size);

        std::vector<int> codepoints;

        int textureWidth = 0;
        int textureHeight = 0;

        for (int c = 32; c < 255; c++) {
            int glyph = stbtt_FindGlyphIndex(&fontInfo, c);
            if (!glyph) continue;
            codepoints.emplace_back(c);

            int x0, y0, x1, y1;
            stbtt_GetGlyphBitmapBoxSubpixel(&fontInfo, glyph, scale, scale, atlas.oversampleH, atlas.oversampleV, &x0, &y0, &x1, &y1);

            textureWidth += x1 - x0 + atlas.padding;
            if (textureHeight < y1 - y0 + atlas.padding)
                textureHeight = y1 - y0 + atlas.padding;
        }
        textureWidth = Math::RoundToNextPow2(textureWidth);
        textureHeight = Math::RoundToNextPow2(textureHeight);

        stbtt_pack_context context;
        stbtt_packedchar* pack = new stbtt_packedchar[codepoints.size()];
        uchar* bitmap = new uchar[(uint64)textureWidth * (uint64)textureHeight];
        stbtt_PackBegin(&context, bitmap, textureWidth, textureHeight, 0, atlas.padding, 0);
        stbtt_PackFontRange(&context, data, fontOffset, (float)size, 32, (int)codepoints.size(), pack);
        stbtt_PackEnd(&context);
        atlas.texture = Texture::Create(textureWidth, textureHeight, TextureInternalFormat::R);
        atlas.texture->Bind();
        atlas.texture->SetData(bitmap, TextureDataFormat::R);

        for (uint32 i = 0; i < codepoints.size(); i++) {
            const stbtt_packedchar& pc = pack[i];
            characters.insert(std::make_pair<wchar, FontCharacter>((wchar)codepoints[i], {
                pc.x0 / (float)textureWidth, pc.y0 / (float)textureHeight, pc.x1 / (float)textureWidth, pc.y1 / (float)textureHeight,
                pc.xoff, -pc.yoff, (float)(pc.x1 - pc.x0), (float)(pc.y1 - pc.y0),
                pc.xadvance
                }));
        }

        delete[] pack;
        delete[] data;
        delete[] bitmap;
#endif
    }

    Font::~Font() {}

    SPR_API Ref<Font> Font::Create(const std::string& path, uint32 size)
    {
        return CreateRef<Font>(path, size);
    }

}