#pragma once

#include "GL/glew.h"

namespace spr {

    enum class PrimitiveType {
        Float = GL_FLOAT,
        Char = GL_BYTE,
        UChar = GL_UNSIGNED_BYTE,
        Int = GL_INT,
        UInt = GL_UNSIGNED_INT
    };

    static int SizeOfPrimitiveType(PrimitiveType type) {
        switch (type)
        {
        case PrimitiveType::Float:
            return sizeof(float);
        case PrimitiveType::Int:
            return sizeof(int);
        case PrimitiveType::Char:
            return sizeof(char);
        case PrimitiveType::UInt:
            return sizeof(unsigned int);
        case PrimitiveType::UChar:
            return sizeof(unsigned char);
        default:
            break;
        }
        return 0;
    }
}