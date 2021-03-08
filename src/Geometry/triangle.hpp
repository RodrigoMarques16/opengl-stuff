#pragma once

#include <array>
#include <glm/ext/vector_float3.hpp>
#include <variant>
#include <SFML/OpenGL.hpp>
#include <Graphics/objects.hpp>

class Triangle {
    using vec3 = glm::vec3;

    const int POSITION     = 0;
    const int COLOR        = 1;
    const int COUNT        = 3;
    const int COLOR_OFFSET = sizeof(vec3);
    const int STRIDE       = 2 * sizeof(vec3);
    const int SIZE         = 6 * sizeof(vec3);
    const vec3 DEFAULT_COLOR = {1.0f, 1.0f, 1.0f};

    vec3 m_data[6];
    VAO m_vao;

    void setup() {
        m_vao.bind();
        VBO(m_data, SIZE, GL_ARRAY_BUFFER).bind();
        add_attribute(POSITION, COUNT, STRIDE, 0);
        add_attribute(1, COUNT, STRIDE, COLOR_OFFSET);
    }

public:

    Triangle(vec3 p0, vec3 p1, vec3 p2) 
        : m_data{p0, DEFAULT_COLOR, p1, DEFAULT_COLOR, p2, DEFAULT_COLOR} {
        setup();
    };

    Triangle(vec3 p0, vec3 c0, vec3 p1, vec3 c1, vec3 p2, vec3 c2) 
        : m_data{p0, c0, p1, c1, p2, c2} {
        setup();
    };

    void draw() {
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};