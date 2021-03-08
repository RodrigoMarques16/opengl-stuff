#pragma once

#include <GL/glew.h>

#include <SFML/OpenGL.hpp>
#include <glm/ext/vector_float3.hpp>

// namespace Graphics {

struct VAO {
    GLuint m_id;
    operator unsigned int() { return m_id; }
    VAO() { glGenVertexArrays(1, &m_id); }
    void bind() { glBindVertexArray(m_id); }
};

struct VBO {
    GLuint m_id;
    GLenum type;

    operator unsigned int() { return m_id; }

    VBO(const void* data, int size, GLenum type) : type(type) { 
        glGenBuffers(1, &m_id);
        glBindBuffer(type, m_id);
        glBufferData(type, size, data, GL_STATIC_DRAW);
    };

    void bind() { 
        glBindBuffer(type, m_id); 
    }
};

void add_attribute(GLuint loc, int size, int stride, int offset) {
    glVertexAttribPointer(loc, size, GL_FLOAT, GL_FALSE, stride, (void*) offset);
    glEnableVertexAttribArray(loc);  
}

struct EBO {};

// };  // namespace Graphics