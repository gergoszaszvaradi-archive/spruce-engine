#pragma once
#include "core.h"
#include "bindable.h"
#include "system/assets.h"
#include "types.h"

#include "STB/stb_image.h"

namespace spr {

    enum class TextureFilterMode {
        Linear = GL_LINEAR,
        Point = GL_NEAREST
    };

    enum class TextureWrapMode {
        ClampToBorder = GL_CLAMP_TO_BORDER,
        ClampToEdge = GL_CLAMP_TO_EDGE,
        Repeat = GL_REPEAT,
        MirroredRepeat = GL_MIRRORED_REPEAT,
        MirroredClampToEdge = GL_MIRROR_CLAMP_TO_EDGE
    };

    enum class TextureDataFormat {
        R = GL_RED,
        RG = GL_RG,
        RGB = GL_RGB,
        BGR = GL_BGR,
        RGBA = GL_RGBA,
        BGRA = GL_BGRA,
        iR = GL_RED_INTEGER,
        iRG = GL_RG_INTEGER,
        iRGB = GL_RGB_INTEGER,
        iBGR = GL_BGR_INTEGER,
        iRGBA = GL_RGBA_INTEGER,
        iBGRA = GL_BGRA_INTEGER,
    };

    enum class TextureInternalFormat {
        R = GL_RED,
        R16 = GL_R16,
        RG = GL_RG,
        RG16 = GL_RG16,
        RGB = GL_RGB,
        RGB16 = GL_RGB16,
        RGBA = GL_RGBA,
        RGBA16 = GL_RGBA16,
        iR = GL_R8I,
        iR16 = GL_R16I,
        iR32 = GL_R32I,
        iRG = GL_RG8I,
        iRG16 = GL_RG16I,
        iRG32 = GL_RG32I,
        iRGB = GL_RGB8I,
        iRGB16 = GL_RGB16I,
        iRGB32 = GL_RGB32I,
        iRGBA = GL_RGBA8I,
        iRGBA16 = GL_RGBA16I,
        iRGBA32 = GL_RGBA32I,
        uiR = GL_R8UI,
        uiR16 = GL_R16UI,
        uiR32 = GL_R32UI,
        uiRG = GL_RG8UI,
        uiRG16 = GL_RG16UI,
        uiRG32 = GL_RG32UI,
        uiRGB = GL_RGB8UI,
        uiRGB16 = GL_RGB16UI,
        uiRGB32 = GL_RGB32UI,
        uiRGBA = GL_RGBA8UI,
        uiRGBA16 = GL_RGBA16UI,
        uiRGBA32 = GL_RGBA32UI,
        fR = GL_R32F,
        fRG = GL_RG32F,
        fRGB = GL_RGB32F,
        fRGBA = GL_RGBA32F,

        Depth24Stencil8 = GL_DEPTH24_STENCIL8
    };

    class Texture : public Bindable, public Asset {
    public:
        SPR_API Texture(uint32 width, uint32 height, TextureInternalFormat internalFormat = TextureInternalFormat::RGBA, TextureDataFormat dataFormat = TextureDataFormat::RGBA);
        SPR_API Texture(const std::string& path, TextureInternalFormat internalFormat);
        SPR_API ~Texture();

        SPR_API void Load(const std::string& path);
        SPR_API void Bind() const override;
        SPR_API void BindToUnit(int i) const;
        SPR_API void Unbind() const override;
        SPR_API void UnbindFromUnit(int i) const;

        SPR_API void Resize(uint32 width, uint32 height);
        SPR_API void SetData(uchar* data, TextureDataFormat format);
        SPR_API void SetSubData(uchar* data, uint32 x, uint32 y, uint32 width, uint32 height);

        SPR_API void SetFilterMode(TextureFilterMode mode);
        SPR_API void SetWrapModeS(TextureWrapMode mode);
        SPR_API void SetWrapModeT(TextureWrapMode mode);

        inline uint32 GetWidth() const { return width; }
        inline uint32 GetHeight() const { return height; }

        SPR_API static Ref<Texture> Create(uint32 width, uint32 height, TextureInternalFormat internalFormat = TextureInternalFormat::RGBA, TextureDataFormat dataFormat = TextureDataFormat::RGBA);
        SPR_API static Ref<Texture> Create(const std::string& path, TextureInternalFormat internalFormat = TextureInternalFormat::RGBA);

    private:
        uint32 width, height;
        int internalFormat, dataFormat, filter, wrapS, wrapT;

    private:
        SPR_API uchar* LoadImageDataFromFile(const std::string& path, uint32& w, uint32& h, TextureDataFormat& format);
    };

}