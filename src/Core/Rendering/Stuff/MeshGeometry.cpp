// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Core/Rendering/Stuff/MeshGeometry.hpp"

namespace core
{
MeshGeometry MeshGeometry::createRectangle(const glm::vec2 &topLeft,
                                           const glm::vec2 &bottomRight,
                                           const ComponentsMask componentsMask)
{
    MeshGeometry result{componentsMask};

    if (componentsMask & Component::Position)
    {
        result.setPositions({
            glm::vec2{topLeft},                   // top left
            glm::vec2{bottomRight.x, topLeft.y},  // top right
            glm::vec2{bottomRight},               // bottom right
            glm::vec2{topLeft.x, bottomRight.y}   // bottom left
        });
    }

    if (componentsMask & Component::TexCoords)
    {
        result.setTexCoords({
            glm::vec2{0.0f, 1.0f},  // top left
            glm::vec2{1.0f, 1.0f},  // top right
            glm::vec2{1.0f, 0.0f},  // bottom right
            glm::vec2{0.0f, 0.0f}   // bottom left
        });
    }

    result.setIndices({
        0,  // top left
        1,  // top right
        2,  // bottom right
        0,  // top left
        2,  // bottom right
        3   // bottom left
    });

    return result;
}


MeshGeometry::MeshGeometry(const MeshGeometry::ComponentsMask componentsMask, const GLenum topology)
    : m_vertexComponents{componentsMask}
    , m_topology{topology}
{
}

uint8_t MeshGeometry::getVertexComponents() const
{
    return m_vertexComponents;
}


GLenum MeshGeometry::getTopology() const
{
    return m_topology;
}


void MeshGeometry::setPositions(const std::vector<glm::vec2> &positions)
{
    m_positions = positions;
}


const std::vector<glm::vec2> &MeshGeometry::getPositions() const
{
    return m_positions;
}


void MeshGeometry::setTexCoords(const std::vector<glm::vec2> &texCoords)
{
    m_texCoords = texCoords;
}


const std::vector<glm::vec2> &MeshGeometry::getTexCoords() const
{
    return m_texCoords;
}


void MeshGeometry::setNormals(const std::vector<glm::vec3> &normals)
{
    m_normals = normals;
}


const std::vector<glm::vec3> &MeshGeometry::getNormals() const
{
    return m_normals;
}


void MeshGeometry::setIndices(const std::vector<uint16_t> &indices)
{
    m_indices = indices;
}


const std::vector<uint16_t> &MeshGeometry::getIndices() const
{
    return m_indices;
}

}  // namespace core
