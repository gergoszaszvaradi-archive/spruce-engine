#pragma once
#include "core.h"
#include "math/vector3D.h"

namespace spr {

    class Mesh {
    public:
        SPR_API Mesh();
        SPR_API Mesh(uint32 vertexCount, uint32 indexCount = 0);

        SPR_API void AddVertex(const Vector3D& position, const Vector2D& texCoord);
        SPR_API void AddVertex(float x, float y, float z, float u, float v);

        SPR_API void AddTringle(uint32 a, uint32 b, uint32 c);

        inline const std::vector<Vector3D>& GetPositions() const { return positions; }
        inline uint32 GetVertexCount() const { return (uint32)positions.size(); }
        inline const std::vector<Vector2D>& GetTexCoords() const { return texCoords; }
        inline const std::vector<uint32>& GetIndices() const { return indices; }
        inline uint32 GetIndexCount() const { return (uint32)indices.size(); }

    private:
        std::vector<Vector3D> positions;
        std::vector<Vector2D> texCoords;

        std::vector<uint32> indices;
    };

}