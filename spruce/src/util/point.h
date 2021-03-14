#pragma once
#include "core.h"

namespace spr {

    template<typename T>
    class Point {
    public:
        T x, y;

        Point() : x(0), y(0) {};
        Point(const T& x, const T& y) : x(x), y(y) {};
    };

    typedef Point<int> Pointi;
    typedef Point<uint32> Pointu;
    typedef Point<float> Pointf;
    typedef Point<double> Pointd;

    template<>
    inline std::string ToString<Pointi>(const Pointi& p) {
        return "Point (" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
    }
    template<>
    inline std::string ToString<Pointu>(const Pointu& p) {
        return "Point (" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
    }
    template<>
    inline std::string ToString<Pointf>(const Pointf& p) {
        return "Point (" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
    }
    template<>
    inline std::string ToString<Pointd>(const Pointd& p) {
        return "Point (" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
    }

}