#include "sprpch.h"
#include "graphics.h"

namespace spr {

    bool Graphics::initialized = false;

    SPR_API void glDebugMsgCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
    {
        Console::LogError("OPENGL ERROR:\n", id, ":", msg);
    }

    void Graphics::Init()
    {
        ASSERT(glfwInit() == GLFW_TRUE, "GLFW did not initialize!");
    }

    void Graphics::InitGL(uint32 width, uint32 height)
    {
        if (initialized)
            return;
        GLenum err = glewInit();
        ASSERT(err == GLEW_OK, "GLEW did not initialize! Error:", glewGetErrorString(err));

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugMsgCallback, 0);

        Renderer::Init(width, height);

        initialized = true;
    }

    SPR_API void Graphics::Dispose()
    {
        Renderer::Dispose();
    }

    SPR_API void Graphics::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    SPR_API void Graphics::SetViewport(uint32 x, uint32 y, uint32 width, uint32 height)
    {
        glViewport(0, 0, width, height);
    }

    SPR_API void Graphics::EnableDepthTest()
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);
    }

    SPR_API void Graphics::DisableDepthTest()
    {
        glDisable(GL_DEPTH_TEST);
    }

    void Graphics::DrawIndexed(const Ref<VertexArray>& vao)
    {
        vao->Bind();
        glDrawElements(GL_TRIANGLES, vao->GetIndexCount(), GL_UNSIGNED_INT, 0);
    }

    void Graphics::DrawBoundIndexed(uint32 count)
    {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    }

}