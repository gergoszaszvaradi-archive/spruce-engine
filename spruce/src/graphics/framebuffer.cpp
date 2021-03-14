#include "sprpch.h"
#include "framebuffer.h"

namespace spr {

    FrameBuffer::FrameBuffer(uint32 width, uint32 height) : width(width), height(height) {}

    FrameBuffer::~FrameBuffer()
    {
        if(id) glDeleteFramebuffers(1, &id);
    }

    SPR_API void FrameBuffer::Bind() const
    {
        if(id) glBindFramebuffer(GL_FRAMEBUFFER, id);
    }

    SPR_API void FrameBuffer::Unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    SPR_API void FrameBuffer::BindAttachment(uint32 id)
    {
        glBindTexture(GL_TEXTURE_2D, textures[id]);
    }

    SPR_API void FrameBuffer::Attach(FrameBufferAttachmentType attachmentType, TextureInternalFormat internalFormat, TextureDataFormat dataFormat)
    {
        attachments.emplace_back(attachmentType, internalFormat, dataFormat);
    }

    SPR_API void FrameBuffer::Attach(const FrameBufferAttachment& attachment)
    {
        attachments.push_back(attachment);
    }

    SPR_API void FrameBuffer::Finilize()
    {
        if (id) {
            glDeleteFramebuffers(1, &id);
            glDeleteTextures((uint32)textures.size(), textures.data());
        }

        textures.resize(attachments.size());

        glCreateFramebuffers(1, &id);
        glBindFramebuffer(GL_FRAMEBUFFER, id);

        if (!attachments.empty()) {
            glGenTextures((uint32)attachments.size(), textures.data());
        }

        uint32 colorAttachmentCount = 0;
        for (uint32 i = 0; i < attachments.size(); i++) {
            glBindTexture(GL_TEXTURE_2D, textures[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            if (attachments[i].type == FrameBufferAttachmentType::Color) {
                glTexImage2D(GL_TEXTURE_2D, 0, (uint32)attachments[i].internalFormat, width, height, 0, (uint32)attachments[i].dataFormat, GL_UNSIGNED_BYTE, nullptr);
                glFramebufferTexture2D(GL_FRAMEBUFFER, (uint32)attachments[i].type + colorAttachmentCount, GL_TEXTURE_2D, textures[i], 0);
                colorAttachmentCount++;
            }
            else {
                glTexStorage2D(GL_TEXTURE_2D, 1, (uint32)attachments[i].internalFormat, width, height);
                glFramebufferTexture2D(GL_FRAMEBUFFER, (uint32)attachments[i].type, GL_TEXTURE_2D, textures[i], 0);
            }
        }

        if (!attachments.empty()) {
            uint32 buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
            glDrawBuffers(colorAttachmentCount, buffers);
        }
        else {
            glDrawBuffer(GL_NONE);
        }

        ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Frame buffer not complete!");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    SPR_API void FrameBuffer::Resize(uint32 width, uint32 height)
    {
        this->width = width;
        this->height = height;
        Finilize();
    }

    void* FrameBuffer::GetPixels(uint32 attachmentID, PrimitiveType channelType) const
    {
        glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentID);
        void* pixels = nullptr; // ? Maybe allocate the space for it?
        glReadPixels(0, 0, width, height, (uint32)attachments[attachmentID].dataFormat, (uint32)channelType, pixels);
        return pixels;
    }

    void* FrameBuffer::GetPixel(uint32 attachmentID, PrimitiveType channelType, uint32 x, uint32 y) const
    {
        Bind();
        glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentID);
        void* pixel = nullptr;
        glReadPixels(x, y, 1, 1, (uint32)attachments[attachmentID].dataFormat, (uint32)channelType, &pixel);
        Unbind();
        return pixel;
    }

    SPR_API Ref<FrameBuffer> FrameBuffer::Create(uint32 width, uint32 height)
    {
        return CreateRef<FrameBuffer>(width, height);
    }

}