#pragma once
#include "core.h"
#include "types.h"
#include "bindable.h"

namespace spr {

    enum class BufferTarget {
        Vertex = GL_ARRAY_BUFFER,
        Index = GL_ELEMENT_ARRAY_BUFFER
    };

    enum class BufferMode {
        Static = GL_STATIC_DRAW,
        Dynamic = GL_DYNAMIC_DRAW
    };

    class Buffer : public Bindable {
    public:
        SPR_API Buffer(BufferTarget target, BufferMode mode);
        SPR_API ~Buffer();

        SPR_API void Bind() const override;
        SPR_API void Unbind() const override;

        SPR_API void Reserve(uint32 size);
        SPR_API void Reserve(uint32 size, uint32 flags);
        SPR_API void SetData(const void* data, uint32 size);
        SPR_API void SetSubData(const void* data, uint32 size, uint32 offset);
        SPR_API void* MapRange(uint32 offset, uint32 count, uint32 flags);
        SPR_API void Clear();

        SPR_API static Ref<Buffer> Create(BufferTarget target, BufferMode mode);

    protected:
        uint32 target_id, mode_id, size;
    };

    class VertexBuffer final : public Buffer {
    public:
        SPR_API VertexBuffer(BufferMode mode);
        static Ref<VertexBuffer> Create(BufferMode mode);
    };

    class IndexBuffer final : public Buffer {
    public:
        SPR_API IndexBuffer(BufferMode mode);
        static Ref<IndexBuffer> Create(BufferMode mode);
    };

    class BufferLayout final {
    public:
        struct BufferLayoutSegment {
            uint32 attribute;
            PrimitiveType type;
            uint32 count;
            BufferLayoutSegment(uint32 attribute, PrimitiveType type, uint32 count) : attribute(attribute), type(type), count(count) {};
        };

        SPR_API BufferLayout();
        SPR_API BufferLayout(const std::vector<BufferLayoutSegment>& segments);

        SPR_API void AddSegment(const BufferLayoutSegment& segment);
        SPR_API void AddSegment(uint32 attribute, PrimitiveType type, uint32 count);

        inline const std::vector<BufferLayoutSegment>& GetSegments() const { return segments; }
        inline uint32 GetStride() const { return stride; }

    private:
        std::vector<BufferLayoutSegment> segments;
        uint32 stride;
    };

    class VertexArray final : public Bindable {
    public:
        SPR_API VertexArray();
        SPR_API ~VertexArray();

        SPR_API void Bind() const override;
        SPR_API void Unbind() const override;

        SPR_API void Attach(uint32 attribute, const Ref<VertexBuffer>& buffer, PrimitiveType type, uint32 count, uint32 stride, uint64 offset);
        SPR_API void Attach(const Ref<VertexBuffer>& buffer, const BufferLayout& layout);
        SPR_API void Attach(const Ref<IndexBuffer>& buffer, uint32 count);

        inline uint32 GetIndexCount() const { return indexCount; }

        static Ref<VertexArray> Create();

    private:
        uint32 indexCount;
    };

}