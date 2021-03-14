#include "sprpch.h"
#include "shader.h"

namespace spr {

    Shader::Shader() {
        id = glCreateProgram();
    }

    Shader::~Shader()
    {
        glDeleteProgram(id);
    }

    SPR_API Ref<Shader> Shader::Create()
    {
        return CreateRef<Shader>();
    }

    SPR_API void Shader::Bind() const
    {
        glUseProgram(id);
    }

    SPR_API void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    SPR_API void Shader::AddSource(ShaderSourceType type, const std::string& src)
    {
        uint32 src_id = glCreateShader((GLenum)type);
        const char* src_c = src.c_str();
        glShaderSource(src_id, 1, &src_c, 0);
        glCompileShader(src_id);
        int compiled = 0;
        glGetShaderiv(src_id, GL_COMPILE_STATUS, &compiled);
        if (compiled == GL_FALSE) {
            int maxl = 0;
            glGetShaderiv(src_id, GL_INFO_LOG_LENGTH, &maxl);
            char* infolog = new char[maxl];
            glGetShaderInfoLog(src_id, maxl, &maxl, infolog);
            glDeleteShader(src_id);
            Console::LogError("SHADER ERROR:\n", infolog);
            delete[] infolog;
            return;
        }
        src_ids.push_back(src_id);
    }

    SPR_API void Shader::LoadFromFile(const std::string& path)
    {
        std::string vertSrc, fragSrc;
        std::string* current = &vertSrc;

        std::ifstream file(path);
        ASSERT(file.is_open(), "Shader file does not exist!");
        std::string line;
        while (std::getline(file, line)) {
            if (line == "#vertex")
                current = &vertSrc;
            else if (line == "#fragment")
                current = &fragSrc;
            else {
                *current += line + "\n";
            }
        }
        file.close();
        AddSource(ShaderSourceType::Vertex, vertSrc);
        AddSource(ShaderSourceType::Fragment, fragSrc);
        Compile();

        name = path;
    }

    SPR_API void Shader::Compile()
    {
        for (uint32 src_id : src_ids)
            glAttachShader(id, src_id);
        glLinkProgram(id);

        int compiled = 0;
        glGetProgramiv(id, GL_LINK_STATUS, &compiled);
        if (compiled == GL_FALSE) {
            int maxl = 0;
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxl);
            char* infolog = new char[maxl];
            glGetProgramInfoLog(id, maxl, &maxl, infolog);
            glDeleteProgram(id);
            Console::LogError("SHADER LINK ERROR:\n", infolog);
            delete[] infolog;
            return;
        }

        for (uint32 src_id : src_ids) {
            glDetachShader(id, src_id);
            glDeleteShader(src_id);
        }
        src_ids.clear();
    }

    SPR_API void Shader::SetInt(const std::string& name, int v) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), v);
    }

    SPR_API void Shader::SetInt(uint32 attribute, int v) const
    {
        glUniform1i(attribute, v);
    }

    SPR_API void Shader::SetFloat(const std::string& name, float v) const
    {
        glUniform1f(glGetUniformLocation(id, name.c_str()), v);
    }

    SPR_API void Shader::SetFloat(uint32 attribute, float v) const
    {
        glUniform1f(attribute, v);
    }

    SPR_API void Shader::SetVector2D(const std::string& name, const Vector2D& v) const
    {
        glUniform2f(glGetUniformLocation(id, name.c_str()), v.x, v.y);
    }

    SPR_API void Shader::SetVector2D(uint32 attribute, const Vector2D& v) const
    {
        glUniform2f(attribute, v.x, v.y);
    }

    SPR_API void Shader::SetVector3D(const std::string& name, const Vector3D& v) const
    {
        glUniform3f(glGetUniformLocation(id, name.c_str()), v.x, v.y, v.z);
    }

    SPR_API void Shader::SetVector3D(uint32 attribute, const Vector3D& v) const
    {
        glUniform3f(attribute, v.x, v.y, v.z);
    }

    SPR_API void Shader::SetVector4D(const std::string& name, const Vector4D& v) const
    {
        glUniform4f(glGetUniformLocation(id, name.c_str()), v.x, v.y, v.z, v.w);
    }

    SPR_API void Shader::SetVector4D(uint32 attribute, const Vector4D& v) const
    {
        glUniform4f(attribute, v.x, v.y, v.z, v.w);
    }

    SPR_API void Shader::SetIntArray(const std::string& name, const int* data, uint32 count) const
    {
        glUniform1iv(glGetUniformLocation(id, name.c_str()), count, data);
    }

    SPR_API void Shader::SetIntArray(uint32 attribute, const int* data, uint32 count) const
    {
        glUniform1iv(attribute, count, data);
    }

    SPR_API void Shader::SetFloatArray(const std::string& name, const float* data, uint32 count) const
    {
        glUniform1fv(glGetUniformLocation(id, name.c_str()), count, data);
    }

    SPR_API void Shader::SetFloatArray(uint32 attribute, const float* data, uint32 count) const
    {
        glUniform1fv(attribute, count, data);
    }

    SPR_API void Shader::SetMatrix4(const std::string& name, const Matrix4& m) const
    {
        glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &m.values[0]);
    }

    SPR_API void Shader::SetMatrix4(uint32 attribute, const Matrix4& m) const
    {
        glUniformMatrix4fv(attribute, 1, GL_FALSE, &m.values[0]);
    }

}