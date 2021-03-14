#include "sprpch.h"
#include "buffer.h"

namespace spr {

    Buffer::Buffer(BufferTarget target, BufferMode mode) : target_id((uint32)target), mode_id((uint32)mode), size(0)
    {
        glGenBuffers(1, &id);
    }

    Buffer::~Buffer()
    {
        glDeleteBuffers(1, &id);
    }

    SPR_API void Buffer::Bind() const
    {
        glBindBuffer(target_id, id);
    }

    SPR_API void Buffer::Unbind() const
    {
        glBindBuffer(target_id, 0);
    }

    SPR_API void Buffer::Reserve(uint32 size)
    {
        this->size = size;
        glBufferData(target_id, size, nullptr, mode_id);
    }

    SPR_API void Buffer::Reserve(uint32 size, uint32 flags)
    {
        this->size = size;
        glBufferStorage(target_id, size, nullptr, flags);
    }

    SPR_API void Buffer::SetData(const void* data, uint32 size)
    {
        this->size = size;
        glBufferData(target_id, size, data, mode_id);
    }

    SPR_API void Buffer::SetSubData(const void* data, uint32 size, uint32 offset)
    {
        glBufferSubData(target_id, offset, size, data);
    }

    SPR_API void* Buffer::MapRange(uint32 offset, uint32 count, uint32 flags)
    {
        return (void*)glMapBufferRange(target_id, offset, size, flags);
    }

    SPR_API void Buffer::Clear()
    {
        SetData(nullptr, size);
    }

    SPR_API Ref<Buffer> Buffer::Create(BufferTarget target, BufferMode mode)
    {
        return CreateRef<Buffer>(target, mode);
    }

    VertexBuffer::VertexBuffer(BufferMode mode) : Buffer(BufferTarget::Vertex, mode) {}

    Ref<VertexBuffer> VertexBuffer::Create(BufferMode mode)
    {
        return CreateRef<VertexBuffer>(mode);
    }

    IndexBuffer::IndexBuffer(BufferMode mode) : Buffer(BufferTarget::Index, mode) {}

    Ref<IndexBuffer> IndexBuffer::Create(BufferMode mode)
    {
        return CreateRef<IndexBuffer>(mode);
    }

    VertexArray::VertexArray() : indexCount(0)
    {
        glGenVertexArrays(1, &id);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &id);
    }

    SPR_API void VertexArray::Bind() const
    {
        glBindVertexArray(id);
    }

    SPR_API void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    SPR_API void VertexArray::Attach(uint32 attribute, const Ref<VertexBuffer>& buffer, PrimitiveType type, uint32 count, uint32 stride, uint64 offset)
    {
        buffer->Bind();
        glEnableVertexAttribArray(attribute);

        switch (type)
        {
        case spr::PrimitiveType::Float:
            glVertexAttribPointer(attribute, count, (uint32)type, GL_FALSE, stride, (const GLvoid*)offset);
            break;
        case spr::PrimitiveType::Char:
        case spr::PrimitiveType::UChar:
        case spr::PrimitiveType::Int:
        case spr::PrimitiveType::UInt:
            glVertexAttribIPointer(attribute, count, (uint32)type, stride, (const GLvoid*)offset);
            break;
        default:
            break;
        }
    }

    SPR_API void VertexArray::Attach(const Ref<VertexBuffer>& buffer, const BufferLayout& layout)
    {
        buffer->Bind();
        uint64 offset = 0;
        for (auto s : layout.GetSegments()) {
            glEnableVertexAttribArray(s.attribute);
            glVertexAttribPointer(s.attribute, s.count, (uint32)s.type, GL_FALSE, layout.GetStride(), (const GLvoid*)offset);
            offset += SizeOfPrimitiveType(s.type) * s.count;
        }
    }

    SPR_API void VertexArray::Attach(const Ref<IndexBuffer>& buffer, uint32 count)
    {
        buffer->Bind();
        indexCount = count;
    }

    Ref<VertexArray> VertexArray::Create()
    {
        return CreateRef<VertexArray>();
    }

    BufferLayout::BufferLayout() : stride(0) {}

    BufferLayout::BufferLayout(const std::vector<BufferLayoutSegment>& segments)
    {
        stride = 0;
        for (auto s : segments) {
            this->segments.push_back(s);
            stride += SizeOfPrimitiveType(s.type) * s.count;
        }
    }

    SPR_API void BufferLayout::AddSegment(const BufferLayoutSegment& segment)
    {
        segments.push_back(segment);
    }

    SPR_API void BufferLayout::AddSegment(uint32 attribute, PrimitiveType type, uint32 count)
    {
        segments.emplace_back(attribute, type, count);
    }

}