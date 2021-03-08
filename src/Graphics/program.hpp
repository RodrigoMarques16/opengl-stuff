#pragma once

#include <vector>
#include <string_view>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>

#include "shader.hpp"

// namespace Graphics {

struct Program {
    Program() = delete;

    Program(std::vector<Shader> shaders);
    ~Program() { glDeleteProgram(m_id); };
    void use() { glUseProgram(m_id); };
    operator unsigned int() { return m_id; }

    void set(const std::string& name, float value);
    void set(const std::string& name, glm::vec2 value);
    void set(const std::string& name, glm::vec3 value);
    void set(const std::string& name, glm::vec4 value);

   private:
    GLuint m_id;
};

Program::Program(std::vector<Shader> shaders) {
    m_id = glCreateProgram();

    for (auto shader : shaders)
        glAttachShader(m_id, shader);

    glLinkProgram(m_id);

    int success;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(m_id, 1024, NULL, infoLog);
        std::cout << "Failed to create program\n"
                  << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    for (auto shader : shaders)
        glDeleteShader(shader);
}

void Program::set(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
};

void Program::set(const std::string& name, glm::vec2 value) {
    glUniform2f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y);
};

void Program::set(const std::string& name, glm::vec3 value) {
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y, value.z);
};

void Program::set(const std::string& name, glm::vec4 value) {
    glUniform4f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y, value.z, value.w);
};

// };  // namespace Graphics