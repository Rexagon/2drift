// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Mesh.hpp"

#include <cstring>

namespace core
{
Mesh::Mesh()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);
}


Mesh::Mesh(const MeshGeometry &geometry)
    : Mesh{}
{
    update(geometry);
}


Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}


void Mesh::update(const MeshGeometry &geometry)
{
    // Calculating buffer layout

    m_indexCount = geometry.getIndices().size();
    m_vertexCount = geometry.getPositions().size();
    m_attributeCount = 0;

    m_topology = geometry.getTopology();

    const auto &vertexComponents = geometry.getVertexComponents();

    size_t bufferSize = 0;

    size_t positionsBufferSize = 0;
    if (vertexComponents & MeshGeometry::Component::Position)
    {
        positionsBufferSize = sizeof(glm::vec2) * geometry.getPositions().size();
        bufferSize += positionsBufferSize;
        ++m_attributeCount;
    }

    size_t texCoordsBufferSize = 0;
    if (vertexComponents & MeshGeometry::Component::TexCoords)
    {
        texCoordsBufferSize = sizeof(glm::vec2) * geometry.getTexCoords().size();
        bufferSize += texCoordsBufferSize;
        ++m_attributeCount;
    }

    size_t normalsBufferSize = 0;
    if (vertexComponents & MeshGeometry::Component::Normal)
    {
        normalsBufferSize = sizeof(glm::vec3) * geometry.getNormals().size();
        bufferSize += normalsBufferSize;
        ++m_attributeCount;
    }

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    std::vector<char> data(bufferSize);

    size_t offset = 0;
    if (vertexComponents & MeshGeometry::Position)
    {
        std::memcpy(&data[0] + offset, geometry.getPositions().data(), positionsBufferSize);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, reinterpret_cast<GLvoid *>(offset));

        offset += positionsBufferSize;
    }

    if (vertexComponents & MeshGeometry::TexCoords)
    {
        std::memcpy(&data[0] + offset, geometry.getTexCoords().data(), texCoordsBufferSize);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, reinterpret_cast<GLvoid *>(offset));

        offset += texCoordsBufferSize;
    }

    if (vertexComponents & MeshGeometry::Normal)
    {
        std::memcpy(&data[0] + offset, geometry.getNormals().data(), normalsBufferSize);
        glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, reinterpret_cast<GLvoid *>(offset));
    }

    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(bufferSize), data.data(), m_bufferUsage);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(uint16_t) * m_indexCount),
                 geometry.getIndices().data(), m_bufferUsage);

    glBindVertexArray(0);
}


void Mesh::draw() const
{
    glBindVertexArray(m_vao);
    for (unsigned int i = 0; i < m_attributeCount; ++i)
    {
        glEnableVertexAttribArray(i);
    }

    glDrawElements(m_topology, static_cast<GLsizei>(m_indexCount), GL_UNSIGNED_SHORT, nullptr);

    for (unsigned int i = 0; i < m_attributeCount; ++i)
    {
        glDisableVertexAttribArray(i);
    }
    glBindVertexArray(0);
}


bool Mesh::isInitialized() const
{
    return m_indexCount > 0;
}


size_t Mesh::getIndexCount() const
{
    return m_indexCount;
}


size_t Mesh::getVertexCount() const
{
    return m_vertexCount;
}


size_t Mesh::getAttributeCount() const
{
    return m_attributeCount;
}


void Mesh::setBufferUsage(GLenum usage)
{
    m_bufferUsage = usage;
}


GLenum Mesh::getBufferUsage() const
{
    return m_bufferUsage;
}

}  // namespace core
