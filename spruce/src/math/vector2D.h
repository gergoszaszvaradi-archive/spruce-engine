#pragma once
#include "core.h"

namespace spr {

    class Vector2D {
    public:
        union { float x, r; };
        union { float y, g; };

        constexpr Vector2D() : x(0), y(0) {}
        constexpr Vector2D(float v) : x(v), y(v) {}
        constexpr Vector2D(float x, float y) : x(x), y(y) {}

        constexpr Vector2D& operator+=(float v);
        constexpr Vector2D& operator+=(const Vector2D& v);
        constexpr Vector2D& operator-=(float v);
        constexpr Vector2D& operator-=(const Vector2D& v);
        constexpr Vector2D& operator*=(float v);
        constexpr Vector2D& operator*=(const Vector2D& v);
        constexpr Vector2D& operator/=(float v);
        constexpr Vector2D& operator/=(const Vector2D& v);

        SPR_API float Length() const;
        SPR_API float SqLength() const;
        SPR_API Vector2D Normalized() const;
        SPR_API void Normalize();

        SPR_API static float Angle(const Vector2D& a, const Vector2D& b);
        SPR_API static float Distance(const Vector2D& a, const Vector2D& b);
        SPR_API static float Dot(const Vector2D& a, const Vector2D& b);
        SPR_API static Vector2D Lerp(const Vector2D& a, const Vector2D& b, float t);
        SPR_API static Vector2D Max(const Vector2D& a, const Vector2D& b);
        SPR_API static Vector2D Min(const Vector2D& a, const Vector2D& b);
    };

    template<>
    inline std::string ToString<Vector2D>(const Vector2D& v) {
        return "Vector2D (" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
    }

    constexpr Vector2D operator-(const Vector2D& v);

    constexpr Vector2D operator+(const Vector2D& v1, float v2);
    constexpr Vector2D operator+(float v1, const Vector2D& v2);
    constexpr Vector2D operator+(const Vector2D& v1, const Vector2D& v2);

    constexpr Vector2D operator-(const Vector2D& v1, float v2);
    constexpr Vector2D operator-(float v1, const Vector2D& v2);
    constexpr Vector2D operator-(const Vector2D& v1, const Vector2D& v2);

    constexpr Vector2D operator*(const Vector2D& v1, float v2);
    constexpr Vector2D operator*(float v1, const Vector2D& v2);
    constexpr Vector2D operator*(const Vector2D& v1, const Vector2D& v2);

    constexpr Vector2D operator/(const Vector2D& v1, float v2);
    constexpr Vector2D operator/(float v1, const Vector2D& v2);
    constexpr Vector2D operator/(const Vector2D& v1, const Vector2D& v2);

    constexpr bool operator==(const Vector2D& v1, const Vector2D& v2);
    constexpr bool operator!=(const Vector2D& v1, const Vector2D& v2);


    inline constexpr Vector2D& Vector2D::operator+=(float v)
    {
        this->x += v;
        this->y += v;
        return *this;
    }

    inline constexpr Vector2D& Vector2D::operator+=(const Vector2D& v)
    {
        this->x += v.x;
        this->y += v.y;
        return *this;
    }

    inline constexpr Vector2D& Vector2D::operator-=(float v)
    {
        this->x -= v;
        this->y -= v;
        return *this;
    }

    inline constexpr Vector2D& Vector2D::operator-=(const Vector2D& v)
    {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }

    inline constexpr Vector2D& Vector2D::operator*=(float v)
    {
        this->x *= v;
        this->y *= v;
        return *this;
    }

    inline constexpr Vector2D& Vector2D::operator*=(const Vector2D& v)
    {
        this->x *= v.x;
        this->y *= v.y;
        return *this;
    }

    inline constexpr Vector2D& Vector2D::operator/=(float v)
    {
        this->x /= v;
        this->y /= v;
        return *this;
    }

    inline constexpr Vector2D& Vector2D::operator/=(const Vector2D& v)
    {
        this->x /= v.x;
        this->y /= v.y;
        return *this;
    }

    inline constexpr Vector2D operator-(const Vector2D& v)
    {
        return Vector2D(-v.x, -v.y);
    }

    inline constexpr Vector2D operator+(const Vector2D& v1, float v2)
    {
        return Vector2D(v1.x + v2, v1.y + v2);
    }

    inline constexpr Vector2D operator+(float v1, const Vector2D& v2)
    {
        return Vector2D(v1 + v2.x, v1 + v2.y);
    }

    inline constexpr Vector2D operator+(const Vector2D& v1, const Vector2D& v2)
    {
        return Vector2D(v1.x + v2.x, v1.y + v2.y);
    }

    inline constexpr Vector2D operator-(const Vector2D& v1, float v2)
    {
        return Vector2D(v1.x - v2, v1.y - v2);
    }

    inline constexpr Vector2D operator-(float v1, const Vector2D& v2)
    {
        return Vector2D(v1 - v2.x, v1 - v2.y);
    }

    inline constexpr Vector2D operator-(const Vector2D& v1, const Vector2D& v2)
    {
        return Vector2D(v1.x - v2.x, v1.y - v2.y);
    }

    inline constexpr Vector2D operator*(const Vector2D& v1, float v2)
    {
        return Vector2D(v1.x * v2, v1.y * v2);
    }

    inline constexpr Vector2D operator*(float v1, const Vector2D& v2)
    {
        return Vector2D(v1 * v2.x, v1 * v2.y);
    }

    inline constexpr Vector2D operator*(const Vector2D& v1, const Vector2D& v2)
    {
        return Vector2D(v1.x * v2.x, v1.y * v2.y);
    }

    inline constexpr Vector2D operator/(const Vector2D& v1, float v2)
    {
        return Vector2D(v1.x / v2, v1.y / v2);
    }

    inline constexpr Vector2D operator/(float v1, const Vector2D& v2)
    {
        return Vector2D(v1 / v2.x, v1 / v2.y);
    }

    inline constexpr Vector2D operator/(const Vector2D& v1, const Vector2D& v2)
    {
        return Vector2D(v1.x / v2.x, v1.y / v2.y);
    }

    inline constexpr bool spr::operator==(const Vector2D& v1, const Vector2D& v2)
    {
        return v1.x == v2.x && v1.y == v2.y;
    }

    inline constexpr bool spr::operator!=(const Vector2D& v1, const Vector2D& v2)
    {
        return !(v1 == v2);
    }

}