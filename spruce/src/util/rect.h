#pragma once
#include "core.h"

namespace spr {

    template<typename T>
    class Rect {
    public:
        T x, y, width, height;

        Rect() : x(0), y(0), width(0), height(0) {};
        Rect(const T& x, const T& y, const T& width, const T& height) : x(x), y(y), width(width), height(height) {};
    };

    typedef Rect<int> Recti;
    typedef Rect<uint32> Rectu;
    typedef Rect<float> Rectf;
    typedef Rect<double> Rectd;

    template<>
    inline std::string ToString<Recti>(const Recti& r) {
        return "Recti (" + std::to_string(r.x) + ", " + std::to_string(r.y) + ", " + std::to_string(r.width) + ", " + std::to_string(r.height) + ")";
    }
    template<>
    inline std::string ToString<Rectu>(const Rectu& r) {
        return "Recti (" + std::to_string(r.x) + ", " + std::to_string(r.y) + ", " + std::to_string(r.width) + ", " + std::to_string(r.height) + ")";
    }
    template<>
    inline std::string ToString<Rectf>(const Rectf& r) {
        return "Recti (" + std::to_string(r.x) + ", " + std::to_string(r.y) + ", " + std::to_string(r.width) + ", " + std::to_string(r.height) + ")";
    }
    template<>
    inline std::string ToString<Rectd>(const Rectd& r) {
        return "Recti (" + std::to_string(r.x) + ", " + std::to_string(r.y) + ", " + std::to_string(r.width) + ", " + std::to_string(r.height) + ")";
    }
}