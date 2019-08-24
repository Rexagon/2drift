#pragma once

#include "Core/Core.hpp"
#include "Core/Rendering/Stuff/MeshGeometry.hpp"

namespace core
{
class Mesh final
{
public:
    /**
     * @brief           Create empty mesh
     */
    explicit Mesh();

    /**
     * @brief           Create mesh from geometry
     * @param geometry  Geometry
     */
    explicit Mesh(const MeshGeometry &geometry);

    /**
     * @brief           Destructor. Destroys all buffers
     */
    ~Mesh();

    /**
     * @brief           Update buffers with new geometry
     * @param geometry  Mesh content
     */
    void update(const MeshGeometry &geometry);

    /**
     * @brief           Draw mesh
     */
    void draw() const;

    /**
     * @return          true if initialized
     */
    bool isInitialized() const;

    /**
     * @return          Index count
     */
    size_t getIndexCount() const;

    /**
     * @return          Vertex count
     */
    size_t getVertexCount() const;

    /**
     * @brief           Get number of mesh vertex components
     * @return          Attribute count
     */
    size_t getAttributeCount() const;

    /**
     * @brief           Set buffer usage mode
     * @param usage     Usage mode. Must be one of GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW,
     * GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY
     */
    void setBufferUsage(GLenum usage);

    /**
     * @brief           Get buffer usage mode
     *
     * GL_STATIC_DRAW is set by default.
     *
     * @return          Usage mode
     */
    GLenum getBufferUsage() const;

private:
    GLuint m_vao = 0;
    GLuint m_vbo = 0;
    GLuint m_ebo = 0;

    size_t m_indexCount = 0;
    size_t m_vertexCount = 0;
    size_t m_attributeCount = 0;

    GLenum m_topology = 0;

    GLenum m_bufferUsage = GL_STATIC_DRAW;
};

}  // namespace core
