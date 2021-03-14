#include "sprpch.h"
#include "matrix4.h"

namespace spr {

    SPR_API Matrix4 spr::Matrix4::Inverse() const
    {
        Matrix4 inv(
            this->values[5] * this->values[10] * this->values[15] -
            this->values[5] * this->values[11] * this->values[14] -
            this->values[9] * this->values[6] * this->values[15] +
            this->values[9] * this->values[7] * this->values[14] +
            this->values[13] * this->values[6] * this->values[11] -
            this->values[13] * this->values[7] * this->values[10],
            
            -this->values[4] * this->values[10] * this->values[15] +
            this->values[4] * this->values[11] * this->values[14] +
            this->values[8] * this->values[6] * this->values[15] -
            this->values[8] * this->values[7] * this->values[14] -
            this->values[12] * this->values[6] * this->values[11] +
            this->values[12] * this->values[7] * this->values[10],
            
            this->values[4] * this->values[9] * this->values[15] -
            this->values[4] * this->values[11] * this->values[13] -
            this->values[8] * this->values[5] * this->values[15] +
            this->values[8] * this->values[7] * this->values[13] +
            this->values[12] * this->values[5] * this->values[11] -
            this->values[12] * this->values[7] * this->values[9],
            
            -this->values[4] * this->values[9] * this->values[14] +
            this->values[4] * this->values[10] * this->values[13] +
            this->values[8] * this->values[5] * this->values[14] -
            this->values[8] * this->values[6] * this->values[13] -
            this->values[12] * this->values[5] * this->values[10] +
            this->values[12] * this->values[6] * this->values[9],
            
            -this->values[1] * this->values[10] * this->values[15] +
            this->values[1] * this->values[11] * this->values[14] +
            this->values[9] * this->values[2] * this->values[15] -
            this->values[9] * this->values[3] * this->values[14] -
            this->values[13] * this->values[2] * this->values[11] +
            this->values[13] * this->values[3] * this->values[10],
            
            this->values[0] * this->values[10] * this->values[15] -
            this->values[0] * this->values[11] * this->values[14] -
            this->values[8] * this->values[2] * this->values[15] +
            this->values[8] * this->values[3] * this->values[14] +
            this->values[12] * this->values[2] * this->values[11] -
            this->values[12] * this->values[3] * this->values[10],
            
            -this->values[0] * this->values[9] * this->values[15] +
            this->values[0] * this->values[11] * this->values[13] +
            this->values[8] * this->values[1] * this->values[15] -
            this->values[8] * this->values[3] * this->values[13] -
            this->values[12] * this->values[1] * this->values[11] +
            this->values[12] * this->values[3] * this->values[9],
            
            this->values[0] * this->values[9] * this->values[14] -
            this->values[0] * this->values[10] * this->values[13] -
            this->values[8] * this->values[1] * this->values[14] +
            this->values[8] * this->values[2] * this->values[13] +
            this->values[12] * this->values[1] * this->values[10] -
            this->values[12] * this->values[2] * this->values[9],
            
            this->values[1] * this->values[6] * this->values[15] -
            this->values[1] * this->values[7] * this->values[14] -
            this->values[5] * this->values[2] * this->values[15] +
            this->values[5] * this->values[3] * this->values[14] +
            this->values[13] * this->values[2] * this->values[7] -
            this->values[13] * this->values[3] * this->values[6],
            
            -this->values[0] * this->values[6] * this->values[15] +
            this->values[0] * this->values[7] * this->values[14] +
            this->values[4] * this->values[2] * this->values[15] -
            this->values[4] * this->values[3] * this->values[14] -
            this->values[12] * this->values[2] * this->values[7] +
            this->values[12] * this->values[3] * this->values[6],
            
            this->values[0] * this->values[5] * this->values[15] -
            this->values[0] * this->values[7] * this->values[13] -
            this->values[4] * this->values[1] * this->values[15] +
            this->values[4] * this->values[3] * this->values[13] +
            this->values[12] * this->values[1] * this->values[7] -
            this->values[12] * this->values[3] * this->values[5],
            
            -this->values[0] * this->values[5] * this->values[14] +
            this->values[0] * this->values[6] * this->values[13] +
            this->values[4] * this->values[1] * this->values[14] -
            this->values[4] * this->values[2] * this->values[13] -
            this->values[12] * this->values[1] * this->values[6] +
            this->values[12] * this->values[2] * this->values[5],
            
            -this->values[1] * this->values[6] * this->values[11] +
            this->values[1] * this->values[7] * this->values[10] +
            this->values[5] * this->values[2] * this->values[11] -
            this->values[5] * this->values[3] * this->values[10] -
            this->values[9] * this->values[2] * this->values[7] +
            this->values[9] * this->values[3] * this->values[6],
            
            this->values[0] * this->values[6] * this->values[11] -
            this->values[0] * this->values[7] * this->values[10] -
            this->values[4] * this->values[2] * this->values[11] +
            this->values[4] * this->values[3] * this->values[10] +
            this->values[8] * this->values[2] * this->values[7] -
            this->values[8] * this->values[3] * this->values[6],
            
            -this->values[0] * this->values[5] * this->values[11] +
            this->values[0] * this->values[7] * this->values[9] +
            this->values[4] * this->values[1] * this->values[11] -
            this->values[4] * this->values[3] * this->values[9] -
            this->values[8] * this->values[1] * this->values[7] +
            this->values[8] * this->values[3] * this->values[5],
                
            this->values[0] * this->values[5] * this->values[10] -
            this->values[0] * this->values[6] * this->values[9] -
            this->values[4] * this->values[1] * this->values[10] +
            this->values[4] * this->values[2] * this->values[9] +
            this->values[8] * this->values[1] * this->values[6] -
            this->values[8] * this->values[2] * this->values[5]
        );

        float det = this->values[0] * inv[0] + this->values[1] * inv[4] + this->values[2] * inv[8] + this->values[3] * inv[12];
        ASSERT(det != 0, "Matrix determinant = 0 when inverting");

        det = 1.0f / det;
        return inv * det;
    }

    SPR_API void Matrix4::Invert()
    {
        *this = this->Inverse();
    }

    SPR_API Matrix4 Matrix4::Ortho(float l, float r, float t, float b, float f, float n)
    {
        return Matrix4(
            2.0f / (r - l), 0.0f,           0.0f,           -((r + l) / (r - l)),
            0.0f,           2.0f / (t - b), 0.0f,           -((t + b) / (t - b)),
            0.0f,           0.0f,          -2.0f / (f - n), -((f + n) / (f - n)),
            0.0f,           0.0f,           0.0f,            1.0f
        );
    }

    SPR_API Matrix4 Matrix4::Ortho(float size, float ratio, float f, float n)
    {
        float l = -size * ratio;
        float r = size * ratio;
        float t = size;
        float b = -size;
        return Matrix4(
            2.0f / (r - l), 0.0f, 0.0f, -((r + l) / (r - l)),
            0.0f, 2.0f / (t - b), 0.0f, -((t + b) / (t - b)),
            0.0f, 0.0f, -2.0f / (f - n), -((f + n) / (f - n)),
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    SPR_API Matrix4 Matrix4::Translation(float x, float y, float z)
    {
        return Matrix4(
            1.0f, 0.0f, 0.0f, x,
            0.0f, 1.0f, 0.0f, y,
            0.0f, 0.0f, 1.0f, z,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    SPR_API Matrix4 Matrix4::Translation(const Vector3D& v)
    {
        return Matrix4(
            1.0f, 0.0f, 0.0f, v.x,
            0.0f, 1.0f, 0.0f, v.y,
            0.0f, 0.0f, 1.0f, v.z,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    SPR_API Matrix4 Matrix4::RotationX(float r)
    {
        float c = cosf(r);
        float s = sinf(r);
        return Matrix4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, c, -s, 0.0f,
            0.0f, s, c, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    SPR_API Matrix4 Matrix4::RotationY(float r)
    {
        float c = cosf(r);
        float s = sinf(r);
        return Matrix4(
             c, 0.0f, s, 0.0f,
             0.0f, 1.0f, 0.0f, 0.0f,
            -s, 0.0f, c, 0.0f,
             0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    SPR_API Matrix4 Matrix4::RotationZ(float r)
    {
        float c = cosf(r);
        float s = sinf(r);
        return Matrix4(
             c,   -s,    0.0f, 0.0f,
             s,    c,    0.0f, 0.0f,
             0.0f, 0.0f, 1.0f, 0.0f,
             0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    SPR_API Matrix4 Matrix4::Scaled(float x, float y, float z)
    {
        return Matrix4(
            x,    0.0f, 0.0f, 0.0f,
            0.0f, y,    0.0f, 0.0f,
            0.0f, 0.0f, z,    0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    SPR_API Matrix4 Matrix4::Scaled(const Vector3D& v)
    {
        return Matrix4(
            v.x,  0.0f, 0.0f, 0.0f,
            0.0f, v.y,  0.0f, 0.0f,
            0.0f, 0.0f, v.z,  0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    //SPR_API Vector4D Matrix4::GetColumn(uint32 i) const
    //{
    //    return glm::column(*this, i);
    //}

    //SPR_API void Matrix4::SetColumn(uint32 i, const Vector4D& v)
    //{
    //    *this = glm::column(*this, i, v);
    //}

    //SPR_API Vector4D Matrix4::GetRow(uint32 i) const
    //{
    //    return glm::row(*this, i);
    //}

    //SPR_API void Matrix4::SetRow(uint32 i, const Vector4D& v)
    //{
    //    *this = glm::row(*this, i, v);
    //}

}
