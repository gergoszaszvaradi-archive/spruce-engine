#include "sprpch.h"
#include "texture.h"

namespace spr {

    Texture::Texture(uint32 width, uint32 height, TextureInternalFormat internalFormat, TextureDataFormat dataFormat) : width(width), height(height), internalFormat((int)internalFormat), dataFormat((int)dataFormat), filter((int)TextureFilterMode::Linear), wrapS((int)TextureWrapMode::Repeat), wrapT((int)TextureWrapMode::Repeat)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &id);
        Bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    }

    Texture::Texture(const std::string& path, TextureInternalFormat internalFormat) : internalFormat((int)internalFormat), filter((int)TextureFilterMode::Linear), wrapS((int)TextureWrapMode::Repeat), wrapT((int)TextureWrapMode::Repeat)
    {
        TextureDataFormat format;
        uchar* data = LoadImageDataFromFile(path, width, height, format);

        glCreateTextures(GL_TEXTURE_2D, 1, &id);
        Bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

        SetData(data, format);
        stbi_image_free(data);

        name = path;
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &id);
    }

    SPR_API void Texture::Load(const std::string& path)
    {
        TextureDataFormat format;
        uchar* data = LoadImageDataFromFile(path, width, height, format);
        SetData(data, format);
        stbi_image_free(data);
    }

    SPR_API void Texture::Bind() const
    {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    SPR_API void Texture::BindToUnit(int i) const
    {
        glBindTextureUnit(i, id);
    }

    SPR_API void Texture::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    SPR_API void Texture::UnbindFromUnit(int i) const
    {
        glBindTextureUnit(i, 0);
    }

    SPR_API void Texture::Resize(uint32 width, uint32 height)
    {
        this->width = width;
        this->height = height;
        SetData(nullptr, (TextureDataFormat)dataFormat);
    }

    SPR_API void Texture::SetData(uchar* data, TextureDataFormat format)
    {
        dataFormat = (int)format;
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, (uint32)PrimitiveType::UChar, data);
    }

    SPR_API void Texture::SetSubData(uchar* data, uint32 x, uint32 y, uint32 width, uint32 height)
    {
        glTextureSubImage2D(id, 0, x, y, width, height, dataFormat, (int)PrimitiveType::UChar, data);
    }

    SPR_API void Texture::SetFilterMode(TextureFilterMode mode)
    {
        filter = (int)mode;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    }

    SPR_API void Texture::SetWrapModeS(TextureWrapMode mode)
    {
        wrapS = (int)mode;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    }

    SPR_API void Texture::SetWrapModeT(TextureWrapMode mode)
    {
        wrapT = (int)mode;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    }

    SPR_API Ref<Texture> Texture::Create(uint32 width, uint32 height, TextureInternalFormat internalFormat, TextureDataFormat dataFormat)
    {
        return CreateRef<Texture>(width, height, internalFormat, dataFormat);
    }

    SPR_API Ref<Texture> Texture::Create(const std::string& path, TextureInternalFormat internalFormat)
    {
        return CreateRef<Texture>(path, internalFormat);
    }

    SPR_API uchar* Texture::LoadImageDataFromFile(const std::string& path, uint32& w, uint32& h, TextureDataFormat& format)
    {
        int c;
        //stbi_set_flip_vertically_on_load(true);
        uchar* data = stbi_load(path.c_str(), (int*)&w, (int*)&h, &c, 0);
        ASSERT(data != nullptr, "Texture not loaded:", path);
        switch (c)
        {
        case 1:
            format = TextureDataFormat::R;
            break;
        case 2:
            format = TextureDataFormat::RG;
            break;
        case 3:
            format = TextureDataFormat::RGB;
            break;
        default:
            format = TextureDataFormat::RGBA;
            break;
        }
        return data;
    }

}
