#include "sprpch.h"
#include "camera.h"

namespace spr {

    Camera::Camera() : mode(ProjectionMode::Orthographic), size(1.0f), fov(60.0f), aspectRatio(1.0f), f(1.0f), n(-1.0f)
    {
        RecalculateProjectionMatrix();
    }

    Camera::Camera(float size) : mode(ProjectionMode::Orthographic), size(size), fov(60.0f), aspectRatio(1.0f), f(1.0f), n(-1.0f)
    {
        RecalculateProjectionMatrix();
    }

    Camera::Camera(float size, float aspectRatio) : mode(ProjectionMode::Orthographic), size(size), fov(60.0f), aspectRatio(aspectRatio), f(1.0f), n(-1.0f)
    {
        RecalculateProjectionMatrix();
    }

    SPR_API void Camera::SetProjectionMode(ProjectionMode mode)
    {
        this->mode = mode;
        isDirty = true;
    }

    SPR_API void Camera::SetSize(float size)
    {
        this->size = size;
        isDirty = true;
    }

    SPR_API void Camera::SetFarClip(float f)
    {
        this->f = f;
        isDirty = true;
    }

    SPR_API void Camera::SetNearClip(float n)
    {
        this->n = n;
        isDirty = true;
    }

    SPR_API void Camera::SetAspectRatio(float aspectRatio)
    {
        this->aspectRatio = aspectRatio;
        isDirty = true;
    }

    SPR_API void Camera::SetPosition(float x, float y, float z)
    {
        position.x = x;
        position.y = y;
        position.z = z;
    }

    SPR_API void Camera::SetPosition(const Vector3D& pos)
    {
        position = pos;
    }

    SPR_API void Camera::SetRotation(float x, float y, float z)
    {
        rotation.x = x;
        rotation.y = y;
        rotation.z = z;
    }

    SPR_API void Camera::SetRotation(const Vector3D& rotation)
    {
        this->rotation = rotation;
    }

    SPR_API void Camera::RecalculateProjectionMatrix()
    {
        if (!isDirty) return;
        switch (mode)
        {
        case spr::ProjectionMode::Orthographic:
            projection = Matrix4::Ortho(size, aspectRatio, f, n);
            break;
        case spr::ProjectionMode::Perspective:
            // TODO implement perspective projection
            break;
        default:
            break;
        }
        RecalculateViewProjectionMatrix();
    }

    SPR_API void Camera::RecalculateViewProjectionMatrix()
    {
        if (!isDirty) return;
        Matrix4 view = Matrix4::Translation(position);
        if (rotation.x != 0) view *= Matrix4::RotationX(rotation.x);
        if (rotation.y != 0) view *= Matrix4::RotationY(rotation.y);
        if (rotation.z != 0) view *= Matrix4::RotationZ(rotation.z);
        viewProjection = projection * view.Inverse();
    }

}