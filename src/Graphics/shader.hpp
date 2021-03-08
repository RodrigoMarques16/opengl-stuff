#pragma once

#include <GL/glew.h>

#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string_view>
#include <vector>

#include "misc.hpp"

// namespace Graphics {

struct Shader {
    Shader(std::string_view path, GLenum type);
    operator unsigned int() { return m_id; }

   private:
    GLuint m_id;
    GLenum m_type;

    void compile(const char* code);
};

Shader::Shader(std::string_view path, GLenum type) {
    m_id = glCreateShader(type);
    m_type = type;
    compile(read_file(path).c_str());
}

void Shader::compile(const char* code) {
    glShaderSource(m_id, 1, &code, NULL);
    glCompileShader(m_id);

    int success;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(m_id, 1024, NULL, infoLog);
        std::cout << "Failed to compile shader\n"
                  << infoLog << std::endl;
        exit(EXIT_FAILURE);
    };
}

// };  // namespace Graphics