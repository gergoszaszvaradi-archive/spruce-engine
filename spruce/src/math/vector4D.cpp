#include "sprpch.h"
#include "Vector4D.h"

namespace spr {

    SPR_API float Vector4D::Length() const
    {
        return sqrtf(x * x + y * y + z * z + w * w);
    }

    SPR_API float Vector4D::SqLength() const
    {
        return x * x + y * y + z * z + w * w;
    }

    SPR_API Vector4D Vector4D::Normalized() const
    {
        // maybe Q_rsqrt?
        float l = Length();
        return Vector4D(x / l, y / l, z / l, w / l);
    }

    SPR_API void Vector4D::Normalize()
    {
        float l = Length();
        x /= l;
        y /= l;
        z /= l;
        w /= l;
    }

    SPR_API float Vector4D::Angle(const Vector4D& a, const Vector4D& b)
    {
        return 0; //! atan2f(b.y - a.y, b.x - a.x); i dont know that to do here
    }

    SPR_API float Vector4D::Distance(const Vector4D& a, const Vector4D& b)
    {
        return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) + (b.z - a.z) * (b.z - a.z) + (b.w - a.w) * (b.w - a.w));
    }

    SPR_API float Vector4D::Dot(const Vector4D& a, const Vector4D& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    SPR_API Vector4D Vector4D::Lerp(const Vector4D& a, const Vector4D& b, float t)
    {
        return a + ((b - a) * t);
    }

    SPR_API Vector4D Vector4D::Max(const Vector4D& a, const Vector4D& b)
    {
        return Vector4D((a.x > b.x ? a.x : b.x), (a.y > b.y ? a.y : b.y), (a.z > b.z ? a.z : b.z), (a.w > b.w ? a.w : b.w)); // TODO: change these to min and max functions
    }

    SPR_API Vector4D Vector4D::Min(const Vector4D& a, const Vector4D& b)
    {
        return Vector4D((a.x < b.x ? a.x : b.x), (a.y < b.y ? a.y : b.y), (a.z < b.z ? a.z : b.z), (a.w < b.w ? a.w : b.w));
    }

}