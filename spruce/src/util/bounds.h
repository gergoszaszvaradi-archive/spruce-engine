#pragma once
#include "core.h"

namespace spr {

    template<typename T>
    class Bounds {
    public:
        T x1, y1, x2, y2;

        Bounds() : x1(0), y1(0), x2(0), y2(0) {};
        Bounds(const T& x1, const T& y1, const T& x2, const T& y2) : x1(x1), y1(y1), x2(x2), y2(y2) {};
    };

    typedef Bounds<int> Boundsi;
    typedef Bounds<uint32> Boundsu;
    typedef Bounds<float> Boundsf;
    typedef Bounds<double> Boundsd;

    template<>
    inline std::string ToString<Boundsi>(const Boundsi& b) {
        return "Recti (" + std::to_string(b.x1) + ", " + std::to_string(b.y1) + ", " + std::to_string(b.x2) + ", " + std::to_string(b.y2) + ")";
    }
    template<>
    inline std::string ToString<Boundsu>(const Boundsu& b) {
        return "Recti (" + std::to_string(b.x1) + ", " + std::to_string(b.y1) + ", " + std::to_string(b.x2) + ", " + std::to_string(b.y2) + ")";
    }
    template<>
    inline std::string ToString<Boundsf>(const Boundsf& b) {
        return "Recti (" + std::to_string(b.x1) + ", " + std::to_string(b.y1) + ", " + std::to_string(b.x2) + ", " + std::to_string(b.y2) + ")";
    }
    template<>
    inline std::string ToString<Boundsd>(const Boundsd& b) {
        return "Recti (" + std::to_string(b.x1) + ", " + std::to_string(b.y1) + ", " + std::to_string(b.x2) + ", " + std::to_string(b.y2) + ")";
    }

}