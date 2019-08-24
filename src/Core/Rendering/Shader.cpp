// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Core/Rendering/Shader.hpp"

#include "Core/Core.hpp"

namespace core
{
Shader::Shader(Core &core)
    : m_renderingManager{core.get<RenderingManager>().lock()}
    , m_id{glCreateProgram()}
{
}


Shader::~Shader()
{
    glDeleteProgram(m_id);

    for (auto &shader : m_shaders)
    {
        glDeleteShader(shader);
    }
}


bool Shader::attachPart(const std::vector<char> &source, const GLenum type, std::string &infoLog)
{
    const GLuint shader = glCreateShader(type);

    auto data = source.data();
    const auto size = static_cast<GLint>(source.size());

    glShaderSource(shader, 1, &data, &size);

    glCompileShader(shader);

    GLint compilationStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationStatus);
    if (compilationStatus == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        infoLog.resize(static_cast<size_t>(infoLogLength));
        glGetShaderInfoLog(shader, infoLogLength, nullptr, &infoLog[0]);

        glDeleteShader(shader);

        return false;
    }

    m_shaders.push_back(shader);
    glAttachShader(m_id, shader);

    return true;
}


bool Shader::link(std::string &infoLog) const
{
    glLinkProgram(m_id);

    GLint linkStatus;
    glGetProgramiv(m_id, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);

        infoLog.resize(static_cast<size_t>(infoLogLength));
        glGetProgramInfoLog(m_id, infoLogLength, nullptr, &infoLog[0]);

        return false;
    }

    return true;
}


void Shader::bind() const
{
    m_renderingManager->setCurrentShaderId(m_id);
}


void Shader::setAttribute(unsigned int index, const std::string &name) const
{
    glBindAttribLocation(m_id, index, name.c_str());
}


void Shader::setUniform(const std::string &name, int data)
{
    glUniform1i(getUniformLocation(name), data);
}


void Shader::setUniform(const std::string &name, float data)
{
    glUniform1f(getUniformLocation(name), data);
}


void Shader::setUniform(const std::string &name, const glm::vec2 &data)
{
    glUniform2f(getUniformLocation(name), data.x, data.y);
}


void Shader::setUniform(const std::string &name, const glm::ivec2 &data)
{
    glUniform2i(getUniformLocation(name), data.x, data.y);
}


void Shader::setUniform(const std::string &name, const glm::vec3 &data)
{
    glUniform3f(getUniformLocation(name), data.x, data.y, data.z);
}


void Shader::setUniform(const std::string &name, const glm::ivec3 &data)
{
    glUniform3i(getUniformLocation(name), data.x, data.y, data.z);
}


void Shader::setUniform(const std::string &name, const glm::vec4 &data)
{
    glUniform4f(getUniformLocation(name), data.x, data.y, data.z, data.w);
}


void Shader::setUniform(const std::string &name, const glm::ivec4 &data)
{
    glUniform4i(getUniformLocation(name), data.x, data.y, data.z, data.w);
}


void Shader::setUniform(const std::string &name, const glm::mat3 &data)
{
    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &data[0][0]);
}


void Shader::setUniform(const std::string &name, const glm::mat4 &data)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &data[0][0]);
}


void Shader::setUniformArray(const std::string &name, int *data, size_t size)
{
    glUniform1iv(getUniformLocation(name), static_cast<GLsizei>(size), data);
}


void Shader::setUniformArray(const std::string &name, float *data, size_t size)
{
    glUniform1fv(getUniformLocation(name), static_cast<GLsizei>(size), data);
}


void Shader::setUniformArray(const std::string &name, glm::vec2 *data, size_t size)
{
    glUniform2fv(getUniformLocation(name), static_cast<GLsizei>(size), &data[0][0]);
}


void Shader::setUniformArray(const std::string &name, glm::ivec2 *data, size_t size)
{
    glUniform2iv(getUniformLocation(name), static_cast<GLsizei>(size), &data[0][0]);
}


void Shader::setUniformArray(const std::string &name, glm::vec3 *data, size_t size)
{
    glUniform3fv(getUniformLocation(name), static_cast<GLsizei>(size), &data[0][0]);
}


void Shader::setUniformArray(const std::string &name, glm::ivec3 *data, size_t size)
{
    glUniform3iv(getUniformLocation(name), static_cast<GLsizei>(size), &data[0][0]);
}


void Shader::setUniformArray(const std::string &name, glm::vec4 *data, size_t size)
{
    glUniform4fv(getUniformLocation(name), static_cast<GLsizei>(size), &data[0][0]);
}


void Shader::setUniformArray(const std::string &name, glm::ivec4 *data, size_t size)
{
    glUniform4iv(getUniformLocation(name), static_cast<GLsizei>(size), &data[0][0]);
}


void Shader::setUniformArray(const std::string &name, glm::mat3 *data, size_t size)
{
    glUniformMatrix3fv(getUniformLocation(name), static_cast<GLsizei>(size), GL_FALSE, &data[0][0][0]);
}


void Shader::setUniformArray(const std::string &name, glm::mat4 *data, size_t size)
{
    glUniformMatrix4fv(getUniformLocation(name), static_cast<GLsizei>(size), GL_FALSE, &data[0][0][0]);
}


GLint Shader::getUniformLocation(const std::string &name)
{
    const auto it = m_uniformLocations.find(name);
    if (it == m_uniformLocations.end())
    {
        const auto location = glGetUniformLocation(m_id, name.c_str());
        m_uniformLocations[name] = location;
        return location;
    }

    return it->second;
}


GLuint Shader::getHandle() const
{
    return m_id;
}

}  // namespace core
