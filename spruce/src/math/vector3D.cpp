#include "sprpch.h"
#include "Vector3D.h"

namespace spr {

    SPR_API float Vector3D::Length() const
    {
        return sqrtf(x * x + y * y + z * z);
    }

    SPR_API float Vector3D::SqLength() const
    {
        return x * x + y * y + z * z;
    }

    SPR_API Vector3D Vector3D::Normalized() const
    {
        // maybe Q_rsqrt?
        float l = Length();
        return Vector3D(x / l, y / l, z / l);
    }

    SPR_API void Vector3D::Normalize()
    {
        float l = Length();
        x /= l;
        y /= l;
        z /= l;
    }

    SPR_API float Vector3D::Angle(const Vector3D& a, const Vector3D& b)
    {
        return 0; //! atan2f(b.y - a.y, b.x - a.x); i dont know that to do here
    }

    SPR_API float Vector3D::Distance(const Vector3D& a, const Vector3D& b)
    {
        return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) + (b.z - a.z) * (b.z - a.z));
    }

    SPR_API float Vector3D::Dot(const Vector3D& a, const Vector3D& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    SPR_API Vector3D Vector3D::Cross(const Vector3D& a, const Vector3D& b)
    {
        return Vector3D(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    }

    SPR_API Vector3D Vector3D::Lerp(const Vector3D& a, const Vector3D& b, float t)
    {
        return a + ((b - a) * t);
    }

    SPR_API Vector3D Vector3D::Max(const Vector3D& a, const Vector3D& b)
    {
        return Vector3D((a.x > b.x ? a.x : b.x), (a.y > b.y ? a.y : b.y), (a.z > b.z ? a.z : b.z)); // TODO: change these to min and max functions
    }

    SPR_API Vector3D Vector3D::Min(const Vector3D& a, const Vector3D& b)
    {
        return Vector3D((a.x < b.x ? a.x : b.x), (a.y < b.y ? a.y : b.y), (a.z < b.z ? a.z : b.z));
    }

}