#pragma once
#include "core.h"
#include "bindable.h"
#include "system/assets.h"
#include "math/vector2D.h"
#include "math/vector3D.h"
#include "math/vector4D.h"
#include "math/matrix4.h"

namespace spr {

    enum class ShaderSourceType {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER
    };

    class Shader : public Bindable, public Asset {
    public:
        SPR_API Shader();
        SPR_API ~Shader();
        static SPR_API Ref<Shader> Create();

        SPR_API void Bind() const override;
        SPR_API void Unbind() const override;

        SPR_API void LoadFromFile(const std::string& path);
        SPR_API void AddSource(ShaderSourceType type, const std::string& src);
        SPR_API void Compile();

        SPR_API void SetInt(const std::string& name, int v) const;
        SPR_API void SetInt(uint32 attribute, int v) const;
        SPR_API void SetFloat(const std::string& name, float v) const;
        SPR_API void SetFloat(uint32 attribute, float v) const;
        SPR_API void SetVector2D(const std::string& name, const Vector2D& v) const;
        SPR_API void SetVector2D(uint32 attribute, const Vector2D& v) const;
        SPR_API void SetVector3D(const std::string& name, const Vector3D& v) const;
        SPR_API void SetVector3D(uint32 attribute, const Vector3D& v) const;
        SPR_API void SetVector4D(const std::string& name, const Vector4D& v) const;
        SPR_API void SetVector4D(uint32 attribute, const Vector4D& v) const;
        SPR_API void SetIntArray(const std::string& name, const int* data, uint32 count) const;
        SPR_API void SetIntArray(uint32 attribute, const int* data, uint32 count) const;
        SPR_API void SetFloatArray(const std::string& name, const float* data, uint32 count) const;
        SPR_API void SetFloatArray(uint32 attribute, const float* data, uint32 count) const;
        SPR_API void SetMatrix4(const std::string& name, const Matrix4& m) const;
        SPR_API void SetMatrix4(uint32 attribute, const Matrix4& m) const;

    private:
        std::vector<uint32> src_ids;
    };

}