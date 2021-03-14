#pragma once
#include "core.h"
#include "math/vector2D.h"
#include "math/vector3D.h"

namespace spr {

    class Vertex {
    public:
        Vertex(const Vector3D& position) : position(position), texCoord(Vector2D(0, 0)), textureID(0) {};
        Vertex(const Vector3D& position, const Vector2D& texCoord) : position(position), texCoord(texCoord), textureID(0) {};
        Vertex(const Vector3D& position, const Vector2D& texCoord, int textureID) : position(position), texCoord(texCoord), textureID(textureID) {};

    public:
        Vector3D position;
        Vector2D texCoord;
        int textureID;
    };

}