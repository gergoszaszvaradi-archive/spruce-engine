#pragma once
#include "core.h"
#include "vector2D.h"

namespace spr {

    class Vector3D {
    public:
        union { float x, r; };
        union { float y, g; };
        union { float z, b; };

        constexpr Vector3D() : x(0), y(0), z(0) {}
        constexpr Vector3D(float v) : x(v), y(v), z(v) {}
        constexpr Vector3D(float x, float y) : x(x), y(y), z(0) {}
        constexpr Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}
        constexpr Vector3D(const Vector2D& v, float z) : x(v.x), y(v.y), z(z) {}

        constexpr operator Vector2D();

        constexpr Vector3D& operator+=(float v);
        constexpr Vector3D& operator+=(const Vector2D& v);
        constexpr Vector3D& operator+=(const Vector3D& v);
        constexpr Vector3D& operator-=(float v);
        constexpr Vector3D& operator-=(const Vector2D& v);
        constexpr Vector3D& operator-=(const Vector3D& v);
        constexpr Vector3D& operator*=(float v);
        constexpr Vector3D& operator*=(const Vector2D& v);
        constexpr Vector3D& operator*=(const Vector3D& v);
        constexpr Vector3D& operator/=(float v);
        constexpr Vector3D& operator/=(const Vector2D& v);
        constexpr Vector3D& operator/=(const Vector3D& v);

        SPR_API float Length() const;
        SPR_API float SqLength() const;
        SPR_API Vector3D Normalized() const;
        SPR_API void Normalize();

        SPR_API static float Angle(const Vector3D& a, const Vector3D& b);
        SPR_API static float Distance(const Vector3D& a, const Vector3D& b);
        SPR_API static float Dot(const Vector3D& a, const Vector3D& b);
        SPR_API static Vector3D Cross(const Vector3D& a, const Vector3D& b);
        SPR_API static Vector3D Lerp(const Vector3D& a, const Vector3D& b, float t);
        SPR_API static Vector3D Max(const Vector3D& a, const Vector3D& b);
        SPR_API static Vector3D Min(const Vector3D& a, const Vector3D& b);
    };

    template<>
    inline std::string ToString<Vector3D>(const Vector3D& v) {
        return "Vector3D (" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")";
    }

    constexpr Vector3D operator-(const Vector3D& v);

    constexpr Vector3D operator+(const Vector3D& v1, float v2);
    constexpr Vector3D operator+(float v1, const Vector3D& v2);
    constexpr Vector3D operator+(const Vector2D& v1, const Vector3D& v2);
    constexpr Vector3D operator+(const Vector3D& v1, const Vector2D& v2);
    constexpr Vector3D operator+(const Vector3D& v1, const Vector3D& v2);

    constexpr Vector3D operator-(const Vector3D& v1, float v2);
    constexpr Vector3D operator-(float v1, const Vector3D& v2);
    constexpr Vector3D operator-(const Vector2D& v1, const Vector3D& v2);
    constexpr Vector3D operator-(const Vector3D& v1, const Vector2D& v2);
    constexpr Vector3D operator-(const Vector3D& v1, const Vector3D& v2);

    constexpr Vector3D operator*(const Vector3D& v1, float v2);
    constexpr Vector3D operator*(float v1, const Vector3D& v2);
    constexpr Vector3D operator*(const Vector2D& v1, const Vector3D& v2);
    constexpr Vector3D operator*(const Vector3D& v1, const Vector2D& v2);
    constexpr Vector3D operator*(const Vector3D& v1, const Vector3D& v2);

    constexpr Vector3D operator/(const Vector3D& v1, float v2);
    constexpr Vector3D operator/(float v1, const Vector3D& v2);
    constexpr Vector3D operator/(const Vector2D& v1, const Vector3D& v2);
    constexpr Vector3D operator/(const Vector3D& v1, const Vector2D& v2);
    constexpr Vector3D operator/(const Vector3D& v1, const Vector3D& v2);

    constexpr bool operator==(const Vector3D& v1, const Vector3D& v2);
    constexpr bool operator!=(const Vector3D& v1, const Vector3D& v2);


    inline constexpr Vector3D::operator Vector2D()
    {
        return Vector2D(x, y);
    }

    inline constexpr Vector3D& Vector3D::operator+=(float v)
    {
        this->x += v;
        this->y += v;
        this->z += v;
        return *this;
    }
    inline constexpr Vector3D& Vector3D::operator+=(const Vector2D& v)
    {
        this->x += v.x;
        this->y += v.y;
        return *this;
    }
    inline constexpr Vector3D& Vector3D::operator+=(const Vector3D& v)
    {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        return *this;
    }

    inline constexpr Vector3D& Vector3D::operator-=(float v)
    {
        this->x -= v;
        this->y -= v;
        this->z -= v;
        return *this;
    }
    inline constexpr Vector3D& Vector3D::operator-=(const Vector2D& v)
    {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }
    inline constexpr Vector3D& Vector3D::operator-=(const Vector3D& v)
    {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        return *this;
    }

    inline constexpr Vector3D& Vector3D::operator*=(float v)
    {
        this->x *= v;
        this->y *= v;
        this->z *= v;
        return *this;
    }
    inline constexpr Vector3D& Vector3D::operator*=(const Vector2D& v)
    {
        this->x *= v.x;
        this->y *= v.y;
        return *this;
    }
    inline constexpr Vector3D& Vector3D::operator*=(const Vector3D& v)
    {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        return *this;
    }

    inline constexpr Vector3D& Vector3D::operator/=(float v)
    {
        this->x /= v;
        this->y /= v;
        this->z /= v;
        return *this;
    }
    inline constexpr Vector3D& Vector3D::operator/=(const Vector2D& v)
    {
        this->x /= v.x;
        this->y /= v.y;
        return *this;
    }
    inline constexpr Vector3D& Vector3D::operator/=(const Vector3D& v)
    {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        return *this;
    }

    inline constexpr Vector3D operator-(const Vector3D& v)
    {
        return Vector3D(-v.x, -v.y, -v.z);
    }

    inline constexpr Vector3D operator+(const Vector3D& v1, float v2)
    {
        return Vector3D(v1.x + v2, v1.y + v2, v1.z + v2);
    }

    inline constexpr Vector3D operator+(float v1, const Vector3D& v2)
    {
        return Vector3D(v1 + v2.x, v1 + v2.y, v1 + v2.z);
    }

    inline constexpr Vector3D operator+(const Vector2D& v1, const Vector3D& v2)
    {
        return Vector3D(v1.x + v2.x, v1.y + v2.y, v2.z);
    }

    inline constexpr Vector3D operator+(const Vector3D& v1, const Vector2D& v2)
    {
        return Vector3D(v1.x + v2.x, v1.y + v2.y, v1.z);
    }

    inline constexpr Vector3D operator+(const Vector3D& v1, const Vector3D& v2)
    {
        return Vector3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    }

    inline constexpr Vector3D operator-(const Vector3D& v1, float v2)
    {
        return Vector3D(v1.x - v2, v1.y - v2, v1.z - v2);
    }

    inline constexpr Vector3D operator-(float v1, const Vector3D& v2)
    {
        return Vector3D(v1 - v2.x, v1 - v2.y, v1 - v2.z);
    }

    inline constexpr Vector3D operator-(const Vector2D& v1, const Vector3D& v2)
    {
        return Vector3D(v1.x - v2.x, v1.y - v2.y, v2.z);
    }

    inline constexpr Vector3D operator-(const Vector3D& v1, const Vector2D& v2)
    {
        return Vector3D(v1.x - v2.x, v1.y - v2.y, v1.z);
    }

    inline constexpr Vector3D operator-(const Vector3D& v1, const Vector3D& v2)
    {
        return Vector3D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    }

    inline constexpr Vector3D operator*(const Vector3D& v1, float v2)
    {
        return Vector3D(v1.x * v2, v1.y * v2, v1.z * v2);
    }

    inline constexpr Vector3D operator*(float v1, const Vector3D& v2)
    {
        return Vector3D(v1 * v2.x, v1 * v2.y, v1 * v2.z);
    }

    inline constexpr Vector3D operator*(const Vector2D& v1, const Vector3D& v2)
    {
        return Vector3D(v1.x * v2.x, v1.y * v2.y, v2.z);
    }

    inline constexpr Vector3D operator*(const Vector3D& v1, const Vector2D& v2)
    {
        return Vector3D(v1.x * v2.x, v1.y * v2.y, v1.z);
    }

    inline constexpr Vector3D operator*(const Vector3D& v1, const Vector3D& v2)
    {
        return Vector3D(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
    }

    inline constexpr Vector3D operator/(const Vector3D& v1, float v2)
    {
        return Vector3D(v1.x / v2, v1.y / v2, v1.z / v2);
    }

    inline constexpr Vector3D operator/(float v1, const Vector3D& v2)
    {
        return Vector3D(v1 / v2.x, v1 / v2.y, v1 / v2.z);
    }

    inline constexpr Vector3D operator/(const Vector2D& v1, const Vector3D& v2)
    {
        return Vector3D(v1.x / v2.x, v1.y / v2.y, v2.z);
    }

    inline constexpr Vector3D operator/(const Vector3D& v1, const Vector2D& v2)
    {
        return Vector3D(v1.x / v2.x, v1.y / v2.y, v1.z);
    }

    inline constexpr Vector3D operator/(const Vector3D& v1, const Vector3D& v2)
    {
        return Vector3D(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
    }

    inline constexpr bool spr::operator==(const Vector3D& v1, const Vector3D& v2)
    {
        return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
    }

    inline constexpr bool spr::operator!=(const Vector3D& v1, const Vector3D& v2)
    {
        return !(v1 == v2);
    }

}