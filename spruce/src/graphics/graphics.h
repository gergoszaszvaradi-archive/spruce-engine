#pragma once
#include "core.h"
#include "graphics/buffer.h"
#include "renderer.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace spr {

    SPR_API void glDebugMsgCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data);

    class Graphics {
    public:
        SPR_API static void Init();
        SPR_API static void InitGL(uint32 width, uint32 height);
        SPR_API static void Dispose();

        SPR_API static void Clear();
        SPR_API static void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height);
        SPR_API static void EnableDepthTest();
        SPR_API static void DisableDepthTest();

        SPR_API static void DrawIndexed(const Ref<VertexArray>& vao);
        SPR_API static void DrawBoundIndexed(uint32 count);

    private:
        static SPR_API bool initialized;
    };

}