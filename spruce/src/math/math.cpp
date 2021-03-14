#include "sprpch.h"
#include "math.h"

namespace spr {

    float Math::PI = 3.14159265359f;

    SPR_API int Math::RoundToNextPow2(int x)
    {
        x--;
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        return ++x;
    }

    SPR_API float Math::ToDeg(float x)
    {
        return x * 180 / PI;
    }

    SPR_API float Math::ToRad(float x)
    {
        return x * PI / 180;
    }
}