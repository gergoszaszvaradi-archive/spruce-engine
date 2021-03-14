#pragma once
#include "core.h"

namespace spr {

    class Math {
    public:
        SPR_API static int RoundToNextPow2(int x);

        SPR_API static float ToDeg(float x);
        SPR_API static float ToRad(float x);

    public:
        SPR_API static float PI;
    };

}