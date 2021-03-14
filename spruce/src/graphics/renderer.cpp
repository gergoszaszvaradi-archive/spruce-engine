#include "sprpch.h"
#include "renderer.h"

namespace spr {

    DrawList::DrawList(uint32 maxVertexCount, uint32 maxIndexCount, uint32 maxTextureCount)
    {
        positionsBase = positionsPtr = new Vector3D[maxVertexCount];
        texCoordsBase = texCoordsPtr = new Vector2D[maxVertexCount];
        colorsBase = colorsPtr = new Vector4D[maxVertexCount];
        texSlotsBase = texSlotsPtr = new uint32[maxVertexCount];
        idsBase = idsPtr = new uint32[maxVertexCount];
        indicesBase = indicesPtr = new uint32[maxIndexCount];
        textures.resize(maxTextureCount);
    }

    DrawList::~DrawList() {}

    RenderContext Renderer::context;
    RendererStats Renderer::stats;

    SPR_API void Renderer::Init(uint32 width, uint32 height)
    {
        context.vboPositions = VertexBuffer::Create(BufferMode::Dynamic);
        context.vboTexCoords = VertexBuffer::Create(BufferMode::Dynamic);
        context.vboColors = VertexBuffer::Create(BufferMode::Dynamic);
        context.vboTexSlots = VertexBuffer::Create(BufferMode::Dynamic);
        context.vboIds = VertexBuffer::Create(BufferMode::Dynamic);
        context.ibo = IndexBuffer::Create(BufferMode::Dynamic);

        context.vao = VertexArray::Create();
        context.vao->Bind();
        context.vao->Attach(0, context.vboPositions, PrimitiveType::Float, 3, 0, 0);
        context.vao->Attach(1, context.vboTexCoords, PrimitiveType::Float, 2, 0, 0);
        context.vao->Attach(2, context.vboColors, PrimitiveType::Float, 4, 0, 0);
        context.vao->Attach(3, context.vboTexSlots, PrimitiveType::UInt, 1, 0, 0);
        context.vao->Attach(4, context.vboIds, PrimitiveType::UInt, 1, 0, 0);
        context.vao->Attach(context.ibo, context.maxIndexCount);

        context.quadPositions[0] = { -0.5f,  0.5f, 0.0f };
        context.quadPositions[1] = {  0.5f,  0.5f, 0.0f };
        context.quadPositions[2] = {  0.5f, -0.5f, 0.0f };
        context.quadPositions[3] = { -0.5f, -0.5f, 0.0f };
        context.quadTexCoords[0] = { 0.0f, 0.0f };
        context.quadTexCoords[1] = { 1.0f, 0.0f };
        context.quadTexCoords[2] = { 1.0f, 1.0f };
        context.quadTexCoords[3] = { 0.0f, 1.0f };

        if (context.maxTextureCount == 0)
            glGetIntegerv(GL_MAX_TEXTURE_UNITS, (int*)&context.maxTextureCount);

        uint32 whiteColor = 0xFFFFFFFF;
        context.whiteTexture = Texture::Create(1, 1);
        context.whiteTexture->Bind();
        context.whiteTexture->SetData((uchar*)&whiteColor, spr::TextureDataFormat::RGBA);

        context.fbo = FrameBuffer::Create(width, height);
        context.fbo->Attach(FrameBufferAttachmentType::Color, TextureInternalFormat::RGBA, TextureDataFormat::RGBA);
        context.fbo->Attach(FrameBufferAttachmentType::Color, TextureInternalFormat::iR32, TextureDataFormat::iR);
        context.fbo->Attach(FrameBufferAttachmentType::Depth, TextureInternalFormat::Depth24Stencil8, TextureDataFormat::RGBA);
        context.fbo->Finilize();

        context.vboScreen = VertexBuffer::Create(BufferMode::Static);
        context.vboScreen->Bind();
        float screenQuad[] = { -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f };
        context.vboScreen->SetData(screenQuad, sizeof(screenQuad));
        context.iboScreen = IndexBuffer::Create(BufferMode::Static);
        context.iboScreen->Bind();
        uint32 screenIndices[] = { 0, 1, 2, 2, 3, 0 };
        context.iboScreen->SetData(screenIndices, sizeof(screenIndices));
        context.vaoScreen = VertexArray::Create();
        context.vaoScreen->Bind();
        context.vaoScreen->Attach(0, context.vboScreen, PrimitiveType::Float, 2, 0, 0);
        context.vaoScreen->Attach(context.iboScreen, 6);

        context.screenShader = AssetManager<Shader>::Get("assets/shaders/screen.glsl"); // ! temp
    }

    SPR_API void Renderer::Dispose()
    {
        for (const DrawList& drawList : context.drawLists) {
            delete[] drawList.positionsBase;
            delete[] drawList.colorsBase;
            delete[] drawList.texCoordsBase;
            delete[] drawList.texSlotsBase;
            delete[] drawList.idsBase;
            delete[] drawList.indicesBase;
        }
    }

    SPR_API void Renderer::BeginFrame()
    {
        context.fbo->Bind();
        Graphics::Clear();
        Graphics::SetViewport(0, 0, context.fbo->GetWidth(), context.fbo->GetHeight());
        Graphics::EnableDepthTest();

        memset(&stats, 0, sizeof(RendererStats));
    }

    SPR_API void Renderer::EndFrame()
    {
        Graphics::DisableDepthTest();
        context.fbo->Unbind();
    }

    SPR_API void Renderer::RenderFrameBuffer()
    {
        Graphics::Clear();
        Graphics::DisableDepthTest();
        context.vaoScreen->Bind();
        context.screenShader->Bind();
        context.screenShader->SetInt("uTexture", 0);
        context.fbo->BindAttachment(0);
        Graphics::DrawBoundIndexed(6);
    }

    SPR_API void Renderer::Begin(const Matrix4& viewProjection)
    {
        context.viewProjection = viewProjection;
    }

    SPR_API void Renderer::Begin(Camera& camera)
    {
        if (camera.IsDirty())
            camera.RecalculateProjectionMatrix();

        Begin(camera.GetViewProjection());
    }

    SPR_API void Renderer::SubmitQuad(uint32 id, const Matrix4& transform, const Ref<Shader>& shader)
    {
        SubmitQuad(id, transform, { 1, 1, 1, 1 }, context.whiteTexture, shader);
    }

    SPR_API void Renderer::SubmitQuad(uint32 id, const Matrix4& transform, const Vector4D& color, const Ref<Shader>& shader)
    {
        SubmitQuad(id, transform, color, context.whiteTexture, shader);
    }

    SPR_API void Renderer::SubmitQuad(uint32 id, const Matrix4& transform, const Vector4D& color, const Ref<Texture>& texture, const Ref<Shader>& shader)
    {
        const Ref<Texture>& textureRef = (texture) ? texture : context.whiteTexture;
        DrawList& drawList = GetAppropriateDrawList(shader, textureRef, 4, 6);
        uint32 textureSlot = GetTextureSlotInDrawList(drawList, textureRef);

        for (uint32 i = 0; i < 4; i++)
            *(drawList.positionsPtr++) = transform * context.quadPositions[i];
        for (uint32 i = 0; i < 4; i++)
            *(drawList.texCoordsPtr++) = context.quadTexCoords[i];
        for (uint32 i = 0; i < 4; i++)
            *(drawList.colorsPtr++) = color;
        for (uint32 i = 0; i < 4; i++)
            *(drawList.texSlotsPtr++) = textureSlot;
        for (uint32 i = 0; i < 4; i++)
            *(drawList.idsPtr++) = id;

        drawList.indicesPtr[0] = drawList.vertexCount + 0;
        drawList.indicesPtr[1] = drawList.vertexCount + 1;
        drawList.indicesPtr[2] = drawList.vertexCount + 2;
        drawList.indicesPtr[3] = drawList.vertexCount + 2;
        drawList.indicesPtr[4] = drawList.vertexCount + 3;
        drawList.indicesPtr[5] = drawList.vertexCount + 0;
        drawList.indicesPtr += 6;

        drawList.vertexCount += 4;
        stats.vertexCount += 4;
        drawList.indexCount += 6;
        stats.indexCount += 6;
    }
    SPR_API void Renderer::SubmitQuad(uint32 id, const Rectf& rect, float depth, const Boundsf& uv, const Vector4D& color, const Ref<Shader>& shader)
    {
        SubmitQuad(id, rect, depth, uv, color, context.whiteTexture, shader);
    }

    SPR_API void Renderer::SubmitQuad(uint32 id, const Rectf& rect, float depth, const Boundsf& uv, const Vector4D& color, const Ref<Texture>& texture, const Ref<Shader>& shader)
    {
        const Ref<Texture>& textureRef = (texture) ? texture : context.whiteTexture;
        DrawList& drawList = GetAppropriateDrawList(shader, textureRef, 4, 6);
        uint32 textureSlot = GetTextureSlotInDrawList(drawList, textureRef);

        drawList.positionsPtr[0] = Vector3D(rect.x, rect.y + rect.height, depth);
        drawList.positionsPtr[1] = Vector3D(rect.x + rect.width, rect.y + rect.height, depth);
        drawList.positionsPtr[2] = Vector3D(rect.x + rect.width, rect.y, depth);
        drawList.positionsPtr[3] = Vector3D(rect.x, rect.y, depth);
        drawList.positionsPtr += 4;

        drawList.texCoordsPtr[0] = Vector2D(uv.x1, uv.y2);
        drawList.texCoordsPtr[1] = Vector2D(uv.x2, uv.y2);
        drawList.texCoordsPtr[2] = Vector2D(uv.x2, uv.y1);
        drawList.texCoordsPtr[3] = Vector2D(uv.x1, uv.y1);
        drawList.texCoordsPtr += 4;

        for (uint32 i = 0; i < 4; i++)
            *(drawList.colorsPtr++) = color;
        for (uint32 i = 0; i < 4; i++)
            *(drawList.texSlotsPtr++) = textureSlot;
        for (uint32 i = 0; i < 4; i++)
            *(drawList.idsPtr++) = id;

        drawList.indicesPtr[0] = drawList.vertexCount + 0;
        drawList.indicesPtr[1] = drawList.vertexCount + 1;
        drawList.indicesPtr[2] = drawList.vertexCount + 2;
        drawList.indicesPtr[3] = drawList.vertexCount + 2;
        drawList.indicesPtr[4] = drawList.vertexCount + 3;
        drawList.indicesPtr[5] = drawList.vertexCount + 0;
        drawList.indicesPtr += 6;

        drawList.vertexCount += 4;
        drawList.indexCount += 6;
    }

    SPR_API void Renderer::End()
    {
        Flush();
    }

    static bool DrawListComparator(const DrawList& a, const DrawList& b) {
        return a.shader->GetID() < b.shader->GetID();
    }

    SPR_API DrawList& Renderer::GetAppropriateDrawList(const Ref<Shader>& shader, const Ref<Texture>& texture, uint32 vertexCount, uint32 indexCount)
    {
        for (DrawList& drawList : context.drawLists) {
            if (drawList.vertexCount + vertexCount <= context.maxVertexCount && drawList.indexCount + indexCount <= context.maxIndexCount) {
                if (drawList.shader->GetID() == shader->GetID()) {
                    if (drawList.textureCount < context.maxTextureCount) {
                        return drawList;
                    }
                    else {
                        auto it = std::find(drawList.textures.begin(), drawList.textures.end(), texture);
                        if (it != drawList.textures.end()) {
                            return drawList;
                        }
                    }
                }
            }
        }

        DrawList& drawList = context.drawLists.emplace_back(context.maxVertexCount, context.maxIndexCount, context.maxTextureCount);
        drawList.shader = shader;

        std::stable_sort(context.drawLists.begin(), context.drawLists.end(), DrawListComparator);

        return drawList;
    }

    SPR_API uint32 Renderer::GetTextureSlotInDrawList(DrawList& drawList, const Ref<Texture>& texture)
    {
        uint32 i;
        for (i = 0; i < drawList.textureCount; i++) {
            if (drawList.textures[i]->GetID() == texture->GetID())
                return i;
        }
        drawList.textures[drawList.textureCount] = texture;
        drawList.textureCount++;
        return i;
    }

    SPR_API void Renderer::Flush()
    {
        uint32 prevShaderID = 0;

        for (DrawList& drawList : context.drawLists) {
            if (drawList.indexCount == 0) continue;

            context.vboPositions->Bind();
            context.vboPositions->SetData(drawList.positionsBase, drawList.vertexCount * sizeof(Vector3D));
            context.vboTexCoords->Bind();
            context.vboTexCoords->SetData(drawList.texCoordsBase, drawList.vertexCount * sizeof(Vector2D));
            context.vboColors->Bind();
            context.vboColors->SetData(drawList.colorsBase, drawList.vertexCount * sizeof(Vector4D));
            context.vboTexSlots->Bind();
            context.vboTexSlots->SetData(drawList.texSlotsBase, drawList.vertexCount * sizeof(uint32));
            context.vboIds->Bind();
            context.vboIds->SetData(drawList.idsBase, drawList.vertexCount * sizeof(int));
            context.ibo->Bind();
            context.ibo->SetData(drawList.indicesBase, drawList.indexCount * sizeof(uint32));

            if (prevShaderID != drawList.shader->GetID()) {
                drawList.shader->Bind();
                drawList.shader->SetMatrix4("uViewProjection", context.viewProjection);
                int textures[32];
                for (int i = 0; i < 32; i++) {
                    textures[i] = i;
                }
                drawList.shader->SetIntArray("uTextures", textures, 32);

                prevShaderID = drawList.shader->GetID();
            }

            for (uint32 i = 0; i < drawList.textureCount; i++)
                drawList.textures[i]->BindToUnit(i);

            context.vao->Bind();
            Graphics::DrawBoundIndexed(drawList.indexCount);
            stats.drawCalls++;

            drawList.positionsPtr = drawList.positionsBase;
            drawList.texCoordsPtr = drawList.texCoordsBase;
            drawList.colorsPtr = drawList.colorsBase;
            drawList.texSlotsPtr = drawList.texSlotsBase;
            drawList.idsPtr = drawList.idsBase;
            drawList.indicesPtr = drawList.indicesBase;
            drawList.vertexCount = 0;
            drawList.indexCount = 0;
            drawList.textureCount = 0;
        }
    }

}