#define GLEW_STATIC

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <chrono>

#include "shader.hpp"
#include <Input/Handler.hpp>
#include <Shaders/triangle.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

sf::Window create_window() {
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    settings.attributeFlags = sf::ContextSettings::Core;
    return sf::Window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OpenGL", sf::Style::Close | sf::Style::Resize, settings);
}

int main() {
    auto window = create_window();
    window.setActive(true);
    window.setVerticalSyncEnabled(true);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        exit(EXIT_FAILURE);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.f);

    float triangle1[] = {
         0.2f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.7f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        -0.25f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
    };

    float triangle2[] = {
        -0.2f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
         0.7f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
         0.25f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 
    }; 

    auto triangle_shader = Shader("..\\..\\src\\Shaders\\triangle.vert", "..\\..\\src\\Shaders\\triangle.frag");

    GLuint vao[2], vbo[2];
    glGenVertexArrays(2, vao);
    glGenBuffers(2, vbo);

    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
    glVertexAttribPointer(TriangleShader::POSITION, TriangleShader::POSITION_SIZE, GL_FLOAT, GL_FALSE, TriangleShader::STRIDE, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(TriangleShader::COLOR, TriangleShader::COLOR_SIZE, GL_FLOAT, GL_FALSE, TriangleShader::STRIDE, (void*)TriangleShader::COLOR_OFFSET);
    glEnableVertexAttribArray(1);

    glBindVertexArray(vao[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
    glVertexAttribPointer(TriangleShader::POSITION, TriangleShader::POSITION_SIZE, GL_FLOAT, GL_FALSE, TriangleShader::STRIDE, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(TriangleShader::COLOR, TriangleShader::COLOR_SIZE, GL_FLOAT, GL_FALSE, TriangleShader::STRIDE, (void*)TriangleShader::COLOR_OFFSET);
    glEnableVertexAttribArray(1);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    InputHandler input_handler;

    sf::Clock clock;

    bool running = true;
    while (running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    running = false;
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        running = false;
                    break;
                case sf::Event::Resized:
                    glViewport(0, 0, event.size.width, event.size.height);
                    break;
                case sf::Event::KeyReleased:
                    input_handler(event.key);
                    break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        triangle_shader.use();

        glBindVertexArray(vao[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(vao[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.display();
    }
}