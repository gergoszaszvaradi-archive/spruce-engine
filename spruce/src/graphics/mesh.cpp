#include "sprpch.h"
#include "mesh.h"

namespace spr {

    Mesh::Mesh() {}

    Mesh::Mesh(uint32 vertexCount, uint32 indexCount)
    {
        positions.reserve(vertexCount);
        if (indexCount > 0)
            indices.reserve(indexCount);
    }

    SPR_API void Mesh::AddVertex(const Vector3D& position, const Vector2D& texCoord)
    {
        positions.push_back(position);
        texCoords.push_back(texCoord);
    }

    SPR_API void Mesh::AddVertex(float x, float y, float z, float u, float v)
    {
        positions.emplace_back(x, y, z);
        texCoords.emplace_back(u, v);
    }

    SPR_API void Mesh::AddTringle(uint32 a, uint32 b, uint32 c)
    {
        indices.push_back(a);
        indices.push_back(b);
        indices.push_back(c);
    }

}