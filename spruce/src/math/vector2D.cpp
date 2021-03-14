#include "sprpch.h"
#include "Vector2D.h"

namespace spr {

    SPR_API float Vector2D::Length() const
    {
        return sqrtf(x * x + y * y);
    }

    SPR_API float Vector2D::SqLength() const
    {
        return x * x + y * y;
    }

    SPR_API Vector2D Vector2D::Normalized() const
    {
        // maybe Q_rsqrt?
        float l = Length();
        return Vector2D(x / l, y / l);
    }

    SPR_API void Vector2D::Normalize()
    {
        float l = Length();
        x /= l;
        y /= l;
    }

    SPR_API float Vector2D::Angle(const Vector2D& a, const Vector2D& b)
    {
        return atan2f(b.y - a.y, b.x - a.x);
    }

    SPR_API float Vector2D::Distance(const Vector2D& a, const Vector2D& b)
    {
        return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
    }

    SPR_API float Vector2D::Dot(const Vector2D& a, const Vector2D& b)
    {
        return a.x * b.x + a.y * b.y;
    }

    SPR_API Vector2D Vector2D::Lerp(const Vector2D& a, const Vector2D& b, float t)
    {
        return a + ((b - a) * t);
    }

    SPR_API Vector2D Vector2D::Max(const Vector2D& a, const Vector2D& b)
    {
        return Vector2D((a.x > b.x ? a.x : b.x), (a.y > b.y ? a.y : b.y));
    }

    SPR_API Vector2D Vector2D::Min(const Vector2D& a, const Vector2D& b)
    {
        return Vector2D((a.x < b.x ? a.x : b.x), (a.y < b.y ? a.y : b.y));
    }

}