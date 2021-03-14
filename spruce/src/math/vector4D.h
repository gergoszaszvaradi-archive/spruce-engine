#pragma once
#include "core.h"
#include "vector2D.h"
#include "vector3D.h"

namespace spr {

    class Vector4D {
    public:
        union { float x, r; };
        union { float y, g; };
        union { float z, b; };
        union { float w, a; };

        constexpr Vector4D() : x(0), y(0), z(0), w(0) {}
        constexpr Vector4D(float v) : x(v), y(v), z(v), w(v) {}
        constexpr Vector4D(float x, float y) : x(x), y(y), z(0), w(1.0f) {} // not sure about w = 1
        constexpr Vector4D(float x, float y, float z) : x(x), y(y), z(z), w(1.0f) {}
        constexpr Vector4D(const Vector3D& v, float w) : x(v.x), y(v.y), z(z), w(w) {}
        constexpr Vector4D(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

        constexpr operator Vector2D();
        constexpr operator Vector3D();

        constexpr Vector4D& operator+=(float v);
        constexpr Vector4D& operator+=(const Vector2D& v);
        constexpr Vector4D& operator+=(const Vector3D& v);
        constexpr Vector4D& operator+=(const Vector4D& v);
        constexpr Vector4D& operator-=(float v);
        constexpr Vector4D& operator-=(const Vector2D& v);
        constexpr Vector4D& operator-=(const Vector3D& v);
        constexpr Vector4D& operator-=(const Vector4D& v);
        constexpr Vector4D& operator*=(float v);
        constexpr Vector4D& operator*=(const Vector2D& v);
        constexpr Vector4D& operator*=(const Vector3D& v);
        constexpr Vector4D& operator*=(const Vector4D& v);
        constexpr Vector4D& operator/=(float v);
        constexpr Vector4D& operator/=(const Vector2D& v);
        constexpr Vector4D& operator/=(const Vector3D& v);
        constexpr Vector4D& operator/=(const Vector4D& v);

        SPR_API float Length() const;
        SPR_API float SqLength() const;
        SPR_API Vector4D Normalized() const;
        SPR_API void Normalize();

        SPR_API static float Angle(const Vector4D& a, const Vector4D& b);
        SPR_API static float Distance(const Vector4D& a, const Vector4D& b);
        SPR_API static float Dot(const Vector4D& a, const Vector4D& b);
        SPR_API static Vector4D Lerp(const Vector4D& a, const Vector4D& b, float t);
        SPR_API static Vector4D Max(const Vector4D& a, const Vector4D& b);
        SPR_API static Vector4D Min(const Vector4D& a, const Vector4D& b);
    };

    template<>
    inline std::string ToString<Vector4D>(const Vector4D& v) {
        return "Vector4D (" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ", " + std::to_string(v.w) + ")";
    }

    constexpr Vector4D operator-(const Vector4D& v);

    constexpr Vector4D operator+(const Vector4D& v1, float v2);
    constexpr Vector4D operator+(float v1, const Vector4D& v2);
    constexpr Vector4D operator+(const Vector2D& v1, const Vector4D& v2);
    constexpr Vector4D operator+(const Vector3D& v1, const Vector4D& v2);
    constexpr Vector4D operator+(const Vector4D& v1, const Vector2D& v2);
    constexpr Vector4D operator+(const Vector4D& v1, const Vector3D& v2);
    constexpr Vector4D operator+(const Vector4D& v1, const Vector4D& v2);

    constexpr Vector4D operator-(const Vector4D& v1, float v2);
    constexpr Vector4D operator-(float v1, const Vector4D& v2);
    constexpr Vector4D operator-(const Vector2D& v1, const Vector4D& v2);
    constexpr Vector4D operator-(const Vector3D& v1, const Vector4D& v2);
    constexpr Vector4D operator-(const Vector4D& v1, const Vector2D& v2);
    constexpr Vector4D operator-(const Vector4D& v1, const Vector3D& v2);
    constexpr Vector4D operator-(const Vector4D& v1, const Vector4D& v2);

    constexpr Vector4D operator*(const Vector4D& v1, float v2);
    constexpr Vector4D operator*(float v1, const Vector4D& v2);
    constexpr Vector4D operator*(const Vector2D& v1, const Vector4D& v2);
    constexpr Vector4D operator*(const Vector3D& v1, const Vector4D& v2);
    constexpr Vector4D operator*(const Vector4D& v1, const Vector2D& v2);
    constexpr Vector4D operator*(const Vector4D& v1, const Vector3D& v2);
    constexpr Vector4D operator*(const Vector4D& v1, const Vector4D& v2);

    constexpr Vector4D operator/(const Vector4D& v1, float v2);
    constexpr Vector4D operator/(float v1, const Vector4D& v2);
    constexpr Vector4D operator/(const Vector2D& v1, const Vector4D& v2);
    constexpr Vector4D operator/(const Vector3D& v1, const Vector4D& v2);
    constexpr Vector4D operator/(const Vector4D& v1, const Vector2D& v2);
    constexpr Vector4D operator/(const Vector4D& v1, const Vector3D& v2);
    constexpr Vector4D operator/(const Vector4D& v1, const Vector4D& v2);

    constexpr bool operator==(const Vector4D& v1, const Vector4D& v2);
    constexpr bool operator!=(const Vector4D& v1, const Vector4D& v2);


    inline constexpr Vector4D::operator Vector2D()
    {
        return Vector2D(x, y);
    }

    inline constexpr Vector4D::operator Vector3D()
    {
        return Vector3D(x, y, z);
    }

    inline constexpr Vector4D& Vector4D::operator+=(float v)
    {
        this->x += v;
        this->y += v;
        this->z += v;
        return *this;
    }
    inline constexpr Vector4D& Vector4D::operator+=(const Vector2D& v)
    {
        this->x += v.x;
        this->y += v.y;
        return *this;
    }
    inline constexpr Vector4D& Vector4D::operator+=(const Vector3D& v)
    {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        return *this;
    }
    inline constexpr Vector4D& Vector4D::operator+=(const Vector4D& v)
    {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        this->w += v.w;
        return *this;
    }

    inline constexpr Vector4D& Vector4D::operator-=(float v)
    {
        this->x -= v;
        this->y -= v;
        this->z -= v;
        return *this;
    }
    inline constexpr Vector4D& Vector4D::operator-=(const Vector2D& v)
    {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }
    inline constexpr Vector4D& Vector4D::operator-=(const Vector3D& v)
    {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        return *this;
    }
    inline constexpr Vector4D& Vector4D::operator-=(const Vector4D& v)
    {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        this->w -= v.w;
        return *this;
    }

    inline constexpr Vector4D& Vector4D::operator*=(float v)
    {
        this->x *= v;
        this->y *= v;
        this->z *= v;
        return *this;
    }
    inline constexpr Vector4D& Vector4D::operator*=(const Vector2D& v)
    {
        this->x *= v.x;
        this->y *= v.y;
        return *this;
    }
    inline constexpr Vector4D& Vector4D::operator*=(const Vector3D& v)
    {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        return *this;
    }
    inline constexpr Vector4D& Vector4D::operator*=(const Vector4D& v)
    {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        this->w *= v.w;
        return *this;
    }

    inline constexpr Vector4D& Vector4D::operator/=(float v)
    {
        this->x /= v;
        this->y /= v;
        this->z /= v;
        return *this;
    }
    inline constexpr Vector4D& Vector4D::operator/=(const Vector2D& v)
    {
        this->x /= v.x;
        this->y /= v.y;
        return *this;
    }
    inline constexpr Vector4D& Vector4D::operator/=(const Vector3D& v)
    {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        return *this;
    }
    inline constexpr Vector4D& Vector4D::operator/=(const Vector4D& v)
    {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        this->w /= v.w;
        return *this;
    }

    inline constexpr Vector4D operator-(const Vector4D& v)
    {
        return Vector4D(-v.x, -v.y, -v.z, -v.w);
    }

    inline constexpr Vector4D operator+(const Vector4D& v1, float v2)
    {
        return Vector4D(v1.x + v2, v1.y + v2, v1.z + v2, v1.w + v2);
    }

    inline constexpr Vector4D operator+(float v1, const Vector4D& v2)
    {
        return Vector4D(v1 + v2.x, v1 + v2.y, v1 + v2.z, v1 + v2.w);
    }

    inline constexpr Vector4D operator+(const Vector2D& v1, const Vector4D& v2)
    {
        return Vector4D(v1.x + v2.x, v1.y + v2.y, v2.z, v2.w);
    }

    inline constexpr Vector4D operator+(const Vector3D& v1, const Vector4D& v2)
    {
        return Vector4D(v1.x + v2.x, v1.y + v2.y, v1.y + v2.z, v2.w);
    }

    inline constexpr Vector4D operator+(const Vector4D& v1, const Vector2D& v2)
    {
        return Vector4D(v1.x + v2.x, v1.y + v2.y, v1.z, v1.w);
    }

    inline constexpr Vector4D operator+(const Vector4D& v1, const Vector3D& v2)
    {
        return Vector4D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w);
    }

    inline constexpr Vector4D operator+(const Vector4D& v1, const Vector4D& v2)
    {
        return Vector4D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
    }

    inline constexpr Vector4D operator-(const Vector4D& v1, float v2)
    {
        return Vector4D(v1.x - v2, v1.y - v2, v1.z - v2, v1.w - v2);
    }

    inline constexpr Vector4D operator-(float v1, const Vector4D& v2)
    {
        return Vector4D(v1 - v2.x, v1 - v2.y, v1 - v2.z, v1 - v2.w);
    }

    inline constexpr Vector4D operator-(const Vector2D& v1, const Vector4D& v2)
    {
        return Vector4D(v1.x - v2.x, v1.y - v2.y, v2.z, v2.w);
    }

    inline constexpr Vector4D operator-(const Vector3D& v1, const Vector4D& v2)
    {
        return Vector4D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v2.w);
    }

    inline constexpr Vector4D operator-(const Vector4D& v1, const Vector2D& v2)
    {
        return Vector4D(v1.x - v2.x, v1.y - v2.y, v1.z, v1.w);
    }

    inline constexpr Vector4D operator-(const Vector4D& v1, const Vector3D& v2)
    {
        return Vector4D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w);
    }

    inline constexpr Vector4D operator-(const Vector4D& v1, const Vector4D& v2)
    {
        return Vector4D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
    }

    inline constexpr Vector4D operator*(const Vector4D& v1, float v2)
    {
        return Vector4D(v1.x * v2, v1.y * v2, v1.z * v2, v1.w * v2);
    }

    inline constexpr Vector4D operator*(float v1, const Vector4D& v2)
    {
        return Vector4D(v1 * v2.x, v1 * v2.y, v1 * v2.z, v1 * v2.w);
    }

    inline constexpr Vector4D operator*(const Vector2D& v1, const Vector4D& v2)
    {
        return Vector4D(v1.x * v2.x, v1.y * v2.y, v2.z, v2.w);
    }

    inline constexpr Vector4D operator*(const Vector3D& v1, const Vector4D& v2)
    {
        return Vector4D(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v2.w);
    }

    inline constexpr Vector4D operator*(const Vector4D& v1, const Vector2D& v2)
    {
        return Vector4D(v1.x * v2.x, v1.y * v2.y, v1.z, v1.w);
    }

    inline constexpr Vector4D operator*(const Vector4D& v1, const Vector3D& v2)
    {
        return Vector4D(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w);
    }

    inline constexpr Vector4D operator*(const Vector4D& v1, const Vector4D& v2)
    {
        return Vector4D(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
    }

    inline constexpr Vector4D operator/(const Vector4D& v1, float v2)
    {
        return Vector4D(v1.x / v2, v1.y / v2, v1.z / v2, v1.w / v2);
    }

    inline constexpr Vector4D operator/(float v1, const Vector4D& v2)
    {
        return Vector4D(v1 / v2.x, v1 / v2.y, v1 / v2.z, v1 / v2.w);
    }

    inline constexpr Vector4D operator/(const Vector2D& v1, const Vector4D& v2)
    {
        return Vector4D(v1.x / v2.x, v1.y / v2.y, v2.z, v2.w);
    }

    inline constexpr Vector4D operator/(const Vector3D& v1, const Vector4D& v2)
    {
        return Vector4D(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v2.w);
    }

    inline constexpr Vector4D operator/(const Vector4D& v1, const Vector2D& v2)
    {
        return Vector4D(v1.x / v2.x, v1.y / v2.y, v1.z, v1.w);
    }

    inline constexpr Vector4D operator/(const Vector4D& v1, const Vector3D& v2)
    {
        return Vector4D(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w);
    }

    inline constexpr Vector4D operator/(const Vector4D& v1, const Vector4D& v2)
    {
        return Vector4D(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
    }

    inline constexpr bool spr::operator==(const Vector4D& v1, const Vector4D& v2)
    {
        return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
    }

    inline constexpr bool spr::operator!=(const Vector4D& v1, const Vector4D& v2)
    {
        return !(v1 == v2);
    }

}