#pragma once
#include "core.h"
#include "bindable.h"
#include "texture.h"

namespace spr {

    enum class FrameBufferAttachmentType {
        Color = GL_COLOR_ATTACHMENT0,
        Depth = GL_DEPTH_ATTACHMENT
    };

    struct FrameBufferAttachment {
        FrameBufferAttachmentType type;
        TextureInternalFormat internalFormat;
        TextureDataFormat dataFormat;

        FrameBufferAttachment(FrameBufferAttachmentType type, TextureInternalFormat internalFormat, TextureDataFormat dataFormat) : type(type), internalFormat(internalFormat), dataFormat(dataFormat) {};
    };

    class FrameBuffer : public Bindable {
    public:
        SPR_API FrameBuffer(uint32 width, uint32 height);
        SPR_API ~FrameBuffer();

        SPR_API void Bind() const override;
        SPR_API void Unbind() const override;
        SPR_API void BindAttachment(uint32 id);

        SPR_API void Attach(FrameBufferAttachmentType attachmentType, TextureInternalFormat internalFormat, TextureDataFormat dataFormat);
        SPR_API void Attach(const FrameBufferAttachment& attachment);
        SPR_API void Finilize();
        SPR_API void Resize(uint32 width, uint32 height);

        inline uint32 GetWidth() const { return width; }
        inline uint32 GetHeight() const { return height; }
        void* GetPixels(uint32 attachmentID, PrimitiveType channelType) const;
        void* GetPixel(uint32 attachmentID, PrimitiveType channelType, uint32 x, uint32 y) const;
        inline uint32 GetFirstColorAttachmentTextureID() const { return textures[0]; }

        SPR_API static Ref<FrameBuffer> Create(uint32 width, uint32 height);

    private:
        uint32 width, height;
        std::vector<FrameBufferAttachment> attachments;
        std::vector<uint32> textures;
    };

}