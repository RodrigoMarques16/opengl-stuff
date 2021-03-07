#pragma once

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "misc.hpp"

class Shader {
    GLuint m_id;
    GLuint m_vertex, m_fragment;

    GLuint load_shader(const std::string& code, GLenum type) {
        GLuint shader = glCreateShader(type);
        auto ptr = code.c_str();
        glShaderSource(shader, 1, &ptr, NULL);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[1024];
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "Failed to compile shader\n"
                      << infoLog << std::endl;
            exit(EXIT_FAILURE);
        };

        return shader;
    };

    void create_program() {
        m_id = glCreateProgram();
        glAttachShader(m_id, m_vertex);
        glAttachShader(m_id, m_fragment);
        glLinkProgram(m_id);

        int success;
        glGetProgramiv(m_id, GL_LINK_STATUS, &success);
        if (!success) {
            std::cout << "Failed to create program\n";
            exit(EXIT_FAILURE);
        }
    }

   public:
    Shader(const std::string& vert_path, const std::string& frag_path) {
        auto vert_code = read_file(vert_path);
        m_vertex = load_shader(vert_code, GL_VERTEX_SHADER);

        auto frag_code = read_file(frag_path);
        m_fragment = load_shader(frag_code, GL_FRAGMENT_SHADER);

        create_program();

        glDeleteShader(m_vertex);
        glDeleteShader(m_fragment);
    }

    Shader(const Shader&) = delete;

    void use() {
        glUseProgram(m_id);
    }

    void set1f(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void set2f(const std::string& name, float value1, float value2) const {
        glUniform2f(glGetUniformLocation(m_id, name.c_str()), value1, value2);
    }

    void set3f(const std::string& name, float value1, float value2, float value3) const {
        glUniform3f(glGetUniformLocation(m_id, name.c_str()), value1, value2, value3);
    }

    void set4f(const std::string& name, float value1, float value2, float value3, float value4) const {
        glUniform4f(glGetUniformLocation(m_id, name.c_str()), value1, value2, value3, value4);
    }
};