#pragma once
#include "core.h"
#include "graphics.h"
#include "vertex.h"
#include "buffer.h"
#include "shader.h"
#include "texture.h"
#include "framebuffer.h"
#include "ui/font.h"
#include "mesh.h"
#include "camera.h"
#include "util/rect.h"
#include "util/bounds.h"
#include "system/assets.h"

namespace spr {

    class DrawList {
    public:
        SPR_API DrawList(uint32 maxVertexCount, uint32 maxIndexCount, uint32 maxTextureCount);
        //SPR_API DrawList(const DrawList&& drawList);
        SPR_API ~DrawList();

    public:
        Vector3D* positionsBase;
        Vector3D* positionsPtr;
        Vector2D* texCoordsBase;
        Vector2D* texCoordsPtr;
        Vector4D* colorsBase;
        Vector4D* colorsPtr;
        uint32* texSlotsBase;
        uint32* texSlotsPtr;
        uint32* idsBase;
        uint32* idsPtr;
        uint32* indicesBase;
        uint32* indicesPtr;

        Ref<Shader> shader;
        std::vector<Ref<Texture>> textures;

        uint32 vertexCount = 0;
        uint32 indexCount = 0;
        uint32 textureCount = 0;
    };

    struct RenderContext {
        std::vector<DrawList> drawLists;
        uint32 maxVertexCount = 40000;
        uint32 maxIndexCount = 60000;
        uint32 maxTextureCount = 0;

        Ref<VertexBuffer> vboPositions;
        Ref<VertexBuffer> vboTexCoords;
        Ref<VertexBuffer> vboColors;
        Ref<VertexBuffer> vboTexSlots;
        Ref<VertexBuffer> vboIds;
        Ref<IndexBuffer> ibo;
        Ref<VertexArray> vao;

        Vector3D quadPositions[4];
        Vector2D quadTexCoords[4];
        Ref<Texture> whiteTexture;
        Matrix4 viewProjection;
        
        Ref<FrameBuffer> fbo;
        Ref<VertexBuffer> vboScreen;
        Ref<IndexBuffer> iboScreen;
        Ref<VertexArray> vaoScreen;
        Ref<Shader> screenShader;
    };

    struct RendererStats {
        uint32 vertexCount = 0;
        uint32 indexCount = 0;
        uint32 drawCalls = 0;
    };

    class Renderer {
    public:
        static SPR_API void Init(uint32 width, uint32 height);
        static SPR_API void Dispose();

        SPR_API static void BeginFrame();
        SPR_API static void EndFrame();
        SPR_API static void RenderFrameBuffer();

        static SPR_API void Begin(const Matrix4& viewProjection);
        static SPR_API void Begin(Camera& camera);

        static SPR_API void SubmitQuad(uint32 id, const Matrix4& transform, const Ref<Shader>& shader);
        static SPR_API void SubmitQuad(uint32 id, const Matrix4& transform, const Vector4D& color, const Ref<Shader>& shader);
        static SPR_API void SubmitQuad(uint32 id, const Matrix4& transform, const Vector4D& color, const Ref<Texture>& texture, const Ref<Shader>& shader);

        static SPR_API void SubmitQuad(uint32 id, const Rectf& rect, float depth, const Boundsf& uv, const Vector4D& color, const Ref<Shader>& shader);
        static SPR_API void SubmitQuad(uint32 id, const Rectf& rect, float depth, const Boundsf& uv, const Vector4D& color, const Ref<Texture>& texture, const Ref<Shader>& shader);

        inline static uint32 GetRendereredTextureID() { return context.fbo->GetFirstColorAttachmentTextureID(); }

        static SPR_API void End();

        inline static const Ref<Texture>& GetWhiteTexture() { return context.whiteTexture; }
        inline static const Ref<FrameBuffer>& GetFrameBuffer() { return context.fbo; } // ! VERY MUCH TEMPORARY
        inline static const RendererStats& GetStats() { return stats; }

    private:
        static SPR_API DrawList& GetAppropriateDrawList(const Ref<Shader>& shader, const Ref<Texture>& texture, uint32 vertexCount, uint32 indexCount);
        static SPR_API uint32 GetTextureSlotInDrawList(DrawList& drawList, const Ref<Texture>& texture);
        static SPR_API void Flush();

    private:
        static SPR_API RenderContext context;
        static SPR_API RendererStats stats;
    };

}