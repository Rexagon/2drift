#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace core
{
class MeshGeometry final
{
public:
    enum Component : uint8_t
    {
        Position = 0x01u,
        TexCoords = 0x02u,
        Normal = 0x04u,
    };

    using ComponentsMask = uint8_t;

    static constexpr auto DEFAULT_COMPONENTS = Position | TexCoords;

    /**
     * @brief               Create rectangle in XY plane
     * @param topLeft       Top left corner of rectangle
     * @param bottomRight   Bottom right corner of rectangle
     * @return              Rectangle
     */
    static MeshGeometry createRectangle(const glm::vec2 &topLeft,
                                        const glm::vec2 &bottomRight,
                                        ComponentsMask componentsMask = DEFAULT_COMPONENTS);


    explicit MeshGeometry(ComponentsMask componentsMask = DEFAULT_COMPONENTS, GLenum topology = GL_TRIANGLES);

    uint8_t getVertexComponents() const;

    GLenum getTopology() const;

    void setPositions(const std::vector<glm::vec2> &positions);
    const std::vector<glm::vec2> &getPositions() const;

    void setTexCoords(const std::vector<glm::vec2> &texCoords);
    const std::vector<glm::vec2> &getTexCoords() const;

    void setNormals(const std::vector<glm::vec3> &normals);
    const std::vector<glm::vec3> &getNormals() const;

    void setIndices(const std::vector<uint16_t> &indices);
    const std::vector<uint16_t> &getIndices() const;

private:
    uint8_t m_vertexComponents;
    GLenum m_topology;

    std::vector<glm::vec2> m_positions{};
    std::vector<glm::vec2> m_texCoords{};
    std::vector<glm::vec3> m_normals{};

    std::vector<uint16_t> m_indices{};
};

}  // namespace core
