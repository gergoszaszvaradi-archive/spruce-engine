#pragma once
#include "core.h"
#include "math/matrix4.h"

namespace spr {

    enum class ProjectionMode {
        Orthographic,
        Perspective
    };

    class Camera {
    public:
        SPR_API Camera();
        SPR_API Camera(float size);
        SPR_API Camera(float size, float aspectRatio);

        inline bool IsDirty() const { return isDirty; }

        inline ProjectionMode GetProjectionMode() const { return mode; }
        SPR_API void SetProjectionMode(ProjectionMode mode);
        inline float GetSize() const { return size; }
        SPR_API void SetSize(float size);
        inline float GetFarClip() const { return f; }
        SPR_API void SetFarClip(float f);
        inline float GetNearClip() const { return n; }
        SPR_API void SetNearClip(float n);
        inline float GetAspectRatio() const { return aspectRatio; }
        SPR_API void SetAspectRatio(float aspectRatio);

        inline const Vector3D& GetPosition() const { return position; }
        SPR_API void SetPosition(float x, float y, float z = 0.0f);
        SPR_API void SetPosition(const Vector3D& pos);
        inline const Vector3D& GetRotation() const { return rotation; }
        SPR_API void SetRotation(float x, float y, float z);
        SPR_API void SetRotation(const Vector3D& rotation);

        SPR_API void RecalculateProjectionMatrix();
        SPR_API void RecalculateViewProjectionMatrix();

        inline const Matrix4& GetProjection() const { return projection; }
        inline const Matrix4& GetViewProjection() const { return viewProjection; }

    private:
        bool isDirty;
        ProjectionMode mode;
        float size, fov, aspectRatio, f, n;

        Vector3D position;
        Vector3D rotation;
        Matrix4 projection;
        Matrix4 viewProjection;
    };

}