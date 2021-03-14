#pragma once
#include "core.h"
#include "vector4D.h"

namespace spr {

    class Matrix4  {
    public:
        float values[16] = { 0.0f };

        constexpr Matrix4();
        constexpr Matrix4(float v);
        constexpr Matrix4(float v1, float v2, float v3, float v4,
            float v5, float v6, float v7, float v8,
            float v9, float v10, float v11, float v12,
            float v13, float v14, float v15, float v16);
        constexpr Matrix4(const Vector4D& c1, const Vector4D& c2, const Vector4D& c3, const Vector4D& c4);

        constexpr float operator[](int i);

        constexpr Matrix4& operator+=(float v);
        constexpr Matrix4& operator+=(const Matrix4& m);
        constexpr Matrix4& operator-=(float v);
        constexpr Matrix4& operator-=(const Matrix4& m);
        constexpr Matrix4& operator*=(float v);
        constexpr Matrix4& operator*=(const Matrix4& m);
        constexpr Matrix4& operator/=(float v);
        constexpr Matrix4& operator/=(const Matrix4& m);

        //SPR_API float Determinant() const;
        SPR_API Matrix4 Inverse() const;
        SPR_API void Invert();
        //SPR_API Matrix4 Transponant() const;
        //SPR_API void Transpose();

        //SPR_API void Translate(float x, float y, float z = 0.0f);
        //SPR_API void Translate(const Matrix4& v);
        //SPR_API void RotateX(float r);
        //SPR_API void RotateY(float r);
        //SPR_API void RotateZ(float r);
        //SPR_API void Scale(float x, float y, float z = 1.0f);
        //SPR_API void Scale(const Matrix4& v);

        static SPR_API Matrix4 Ortho(float l, float r, float t, float b, float f, float n);
        static SPR_API Matrix4 Ortho(float size, float ratio, float f, float n);
        static SPR_API Matrix4 Translation(float x, float y, float z = 0.0f);
        static SPR_API Matrix4 Translation(const Vector3D& v);
        static SPR_API Matrix4 RotationX(float r);
        static SPR_API Matrix4 RotationY(float r);
        static SPR_API Matrix4 RotationZ(float r);
        static SPR_API Matrix4 Scaled(float x, float y, float z = 1.0f);
        static SPR_API Matrix4 Scaled(const Vector3D& v);

        //SPR_API Vector4D GetColumn(uint32 i) const;
        //SPR_API void SetColumn(uint32 i, const Vector4D& v);
        //SPR_API Vector4D GetRow(uint32 i) const;
        //SPR_API void SetRow(uint32 i, const Vector4D& v);
    };

    constexpr Matrix4 operator-(const Matrix4& v);

    constexpr Matrix4 operator+(const Matrix4& v1, float v2);
    constexpr Matrix4 operator+(float v1, const Matrix4& v2);
    constexpr Matrix4 operator+(const Matrix4& v1, const Matrix4& v2);

    constexpr Matrix4 operator-(const Matrix4& v1, float v2);
    constexpr Matrix4 operator-(float v1, const Matrix4& v2);
    constexpr Matrix4 operator-(const Matrix4& v1, const Matrix4& v2);

    constexpr Matrix4 operator*(const Matrix4& v1, float v2);
    constexpr Vector2D operator*(const Matrix4& v1, const Vector2D& v2);
    constexpr Vector3D operator*(const Matrix4& v1, const Vector3D& v2);
    constexpr Vector4D operator*(const Matrix4& v1, const Vector4D& v2);
    constexpr Matrix4 operator*(float v1, const Matrix4& v2);
    constexpr Matrix4 operator*(const Matrix4& v1, const Matrix4& v2);

    constexpr Matrix4 operator/(const Matrix4& v1, float v2);
    constexpr Matrix4 operator/(float v1, const Matrix4& v2);

    constexpr bool operator==(const Matrix4& v1, const Matrix4& v2);
    constexpr bool operator!=(const Matrix4& v1, const Matrix4& v2);

    inline constexpr Matrix4::Matrix4()
    {
        for (uint32 i = 0; i < 4; i++) {
            values[i * 4 + i] = 1.0f;
        }
    }
    inline constexpr spr::Matrix4::Matrix4(float v)
    {
        for (uint32 i = 0; i < 4; i++) {
            values[i * 4 + i] = v;
        }
    }
    inline constexpr Matrix4::Matrix4(float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8, float v9, float v10, float v11, float v12, float v13, float v14, float v15, float v16)
    {
        values[0] = v1;
        values[1] = v5;
        values[2] = v9;
        values[3] = v13;
        values[4] = v2;
        values[5] = v6;
        values[6] = v10;
        values[7] = v14;
        values[8] = v3;
        values[9] = v7;
        values[10] = v11;
        values[11] = v15;
        values[12] = v4;
        values[13] = v8;
        values[14] = v12;
        values[15] = v16;
    }
    inline constexpr Matrix4::Matrix4(const Vector4D& c1, const Vector4D& c2, const Vector4D& c3, const Vector4D& c4)
    {
        values[0] = c1.x;
        values[1] = c1.y;
        values[2] = c1.z;
        values[3] = c1.w;
        values[4] = c2.x;
        values[5] = c2.y;
        values[6] = c2.z;
        values[7] = c2.w;
        values[8] = c3.x;
        values[9] = c3.y;
        values[10] = c3.z;
        values[11] = c3.w;
        values[12] = c4.x;
        values[13] = c4.y;
        values[14] = c4.z;
        values[15] = c4.w;
    }

    inline constexpr float Matrix4::operator[](int i)
    {
        return values[i];
    }

    inline constexpr Matrix4& Matrix4::operator+=(float v)
    {
        __m128 r = { v, v, v, v };
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&values[i * 4], _mm_add_ps(_mm_load_ps(&values[i * 4]), r));
        }
        return *this;
    }
    inline constexpr Matrix4& Matrix4::operator+=(const Matrix4& m)
    {
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&values[i * 4], _mm_add_ps(_mm_load_ps(&values[i * 4]), _mm_load_ps(&m.values[i * 4])));
        }
        return *this;
    }

    inline constexpr Matrix4& Matrix4::operator-=(float v)
    {
        __m128 r = { v, v, v, v };
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&values[i * 4], _mm_sub_ps(_mm_load_ps(&values[i * 4]), r));
        }
        return *this;
    }
    inline constexpr Matrix4& Matrix4::operator-=(const Matrix4& m)
    {
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&values[i * 4], _mm_sub_ps(_mm_load_ps(&values[i * 4]), _mm_load_ps(&m.values[i * 4])));
        }
        return *this;
    }

    inline constexpr Matrix4& Matrix4::operator*=(float v)
    {
        __m128 r = { v, v, v, v };
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&values[i * 4], _mm_mul_ps(_mm_load_ps(&values[i * 4]), r));
        }
        return *this;
    }
    inline constexpr Matrix4& Matrix4::operator*=(const Matrix4& m)
    {
        __m128 row[4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
        __m128 sum[4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
        for (uint32 i = 0; i < 4; i++) row[i] = _mm_load_ps(&values[i * 4]);
        for (uint32 i = 0; i < 4; i++) {
            for (uint32 j = 0; j < 4; j++) {
                sum[i] = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.values[i * 4 + j]), row[j]), sum[i]);
            }
        }
        for (uint32 i = 0; i < 4; i++) _mm_store_ps(&values[i * 4], sum[i]);
        return *this;
    }

    inline constexpr Matrix4& Matrix4::operator/=(float v)
    {
        __m128 r = { v, v, v, v };
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&values[i * 4], _mm_div_ps(_mm_load_ps(&values[i * 4]), r));
        }
        return *this;
    }
    inline constexpr Matrix4& Matrix4::operator/=(const Matrix4& m)
    {
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&values[i * 4], _mm_div_ps(_mm_load_ps(&values[i * 4]), _mm_load_ps(&m.values[i * 4])));
        }
        return *this;
    }

    inline constexpr Matrix4 spr::operator-(const Matrix4& v)
    {
        Matrix4 result;
        __m128 r = { -1.0f, -1.0f, -1.0f, -1.0f };
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&result.values[i * 4], _mm_mul_ps(_mm_load_ps(&v.values[i * 4]), r));
        }
        return result;
    }

    inline constexpr Matrix4 operator+(const Matrix4& v1, float v2)
    {
        Matrix4 result;
        __m128 r = { v2, v2, v2, v2 };
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&result.values[i * 4], _mm_add_ps(_mm_load_ps(&v1.values[i * 4]), r));
        }
        return result;
    }
    inline constexpr Matrix4 operator+(float v1, const Matrix4& v2)
    {
        Matrix4 result;
        __m128 r = { v1, v1, v1, v1 };
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&result.values[i * 4], _mm_add_ps(_mm_load_ps(&v2.values[i * 4]), r));
        }
        return result;
    }
    inline constexpr Matrix4 operator+(const Matrix4& v1, const Matrix4& v2)
    {
        Matrix4 result;
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&result.values[i * 4], _mm_add_ps(_mm_load_ps(&v1.values[i * 4]), _mm_load_ps(&v2.values[i * 4])));
        }
        return result;
    }

    inline constexpr Matrix4 operator-(const Matrix4& v1, float v2)
    {
        Matrix4 result;
        __m128 r = { v2, v2, v2, v2 };
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&result.values[i * 4], _mm_sub_ps(_mm_load_ps(&v1.values[i * 4]), r));
        }
        return result;
    }
    inline constexpr Matrix4 operator-(float v1, const Matrix4& v2)
    {
        Matrix4 result;
        __m128 r = { v1, v1, v1, v1 };
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&result.values[i * 4], _mm_sub_ps(_mm_load_ps(&v2.values[i * 4]), r));
        }
        return result;
    }
    inline constexpr Matrix4 operator-(const Matrix4& v1, const Matrix4& v2)
    {
        Matrix4 result;
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&result.values[i * 4], _mm_sub_ps(_mm_load_ps(&v1.values[i * 4]), _mm_load_ps(&v2.values[i * 4])));
        }
        return result;
    }

    inline constexpr Matrix4 operator*(const Matrix4& v1, float v2)
    {
        Matrix4 result;
        __m128 r = { v2, v2, v2, v2 };
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&result.values[i * 4], _mm_mul_ps(_mm_load_ps(&v1.values[i * 4]), r));
        }
        return result;
    }
    inline constexpr Vector2D operator*(const Matrix4& v1, const Vector2D& v2)
    {
        return Vector2D(v1.values[0] * v2.x + v1.values[4] * v2.y + v1.values[12], v1.values[1] * v2.x + v1.values[5] * v2.y + v1.values[13]);
    }
    inline constexpr Vector3D operator*(const Matrix4& v1, const Vector3D& v2)
    {
        return Vector3D(
            v1.values[0] * v2.x + v1.values[4] * v2.y + v1.values[8] * v2.z + v1.values[12],
            v1.values[1] * v2.x + v1.values[5] * v2.y + v1.values[9] * v2.z + v1.values[13],
            v1.values[2] * v2.x + v1.values[6] * v2.y + v1.values[10] * v2.z + v1.values[14]
        );
    }
    inline constexpr Vector4D operator*(const Matrix4& v1, const Vector4D& v2)
    {
        return Vector4D(
            v1.values[0] * v2.x + v1.values[4] * v2.y + v1.values[8] * v2.z + v1.values[12] * v2.w,
            v1.values[1] * v2.x + v1.values[5] * v2.y + v1.values[9] * v2.z + v1.values[13] * v2.w,
            v1.values[2] * v2.x + v1.values[6] * v2.y + v1.values[10] * v2.z + v1.values[14] * v2.w,
            v1.values[3] * v2.x + v1.values[7] * v2.y + v1.values[11] * v2.z + v1.values[15] * v2.w
        );
    }
    inline constexpr Matrix4 operator*(float v1, const Matrix4& v2)
    {
        Matrix4 result;
        __m128 r = { v1, v1, v1, v1 };
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&result.values[i * 4], _mm_mul_ps(_mm_load_ps(&v2.values[i * 4]), r));
        }
        return result;
    }
    inline constexpr Matrix4 operator*(const Matrix4& v1, const Matrix4& v2)
    {
        Matrix4 result;
        __m128 row[4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
        __m128 sum[4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
        for (uint32 i = 0; i < 4; i++) row[i] = _mm_load_ps(&v1.values[i * 4]);
        for (uint32 i = 0; i < 4; i++) {
            for (uint32 j = 0; j < 4; j++) {
                sum[i] = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(v2.values[i * 4 + j]), row[j]), sum[i]);
            }
        }
        for (uint32 i = 0; i < 4; i++) _mm_store_ps(&result.values[i * 4], sum[i]);
        return result;
    }

    inline constexpr Matrix4 operator/(const Matrix4& v1, float v2)
    {
        Matrix4 result;
        __m128 r = { v2, v2, v2, v2 };
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&result.values[i * 4], _mm_div_ps(_mm_load_ps(&v1.values[i * 4]), r));
        }
        return result;
    }

    inline constexpr Matrix4 operator/(float v1, const Matrix4& v2)
    {
        Matrix4 result;
        __m128 r = { v1, v1, v1, v1 };
        for (uint32 i = 0; i < 4; i++) {
            _mm_store_ps(&result.values[i * 4], _mm_div_ps(_mm_load_ps(&v2.values[i * 4]), r));
        }
        return result;
    }

    inline constexpr bool operator==(const Matrix4& v1, const Matrix4& v2)
    {
        for (uint32 i = 0; i < 16; i++) {
            if (v1.values[i] != v2.values[i])
                return false;
        }
        return true;
    }

    inline constexpr bool operator!=(const Matrix4& v1, const Matrix4& v2)
    {
        return !(v1 == v2);
    }

}