#pragma once
#include "core.h"

namespace spr {

    template<typename T>
    class Size {
    public:
        T width, height;

        Size() : width(0), height(0) {};
        Size(const T& width, const T& height) : width(width), height(height) {};
    };

    typedef Size<int> Sizei;
    typedef Size<uint32> Sizeu;
    typedef Size<float> Sizef;
    typedef Size<double> Sized;

    template<>
    inline std::string ToString<Sizei>(const Sizei& s) {
        return "Size (" + std::to_string(s.width) + ", " + std::to_string(s.height) + ")";
    }
    template<>
    inline std::string ToString<Sizeu>(const Sizeu& s) {
        return "Size (" + std::to_string(s.width) + ", " + std::to_string(s.height) + ")";
    }
    template<>
    inline std::string ToString<Sizef>(const Sizef& s) {
        return "Size (" + std::to_string(s.width) + ", " + std::to_string(s.height) + ")";
    }
    template<>
    inline std::string ToString<Sized>(const Sized& s) {
        return "Size (" + std::to_string(s.width) + ", " + std::to_string(s.height) + ")";
    }

}