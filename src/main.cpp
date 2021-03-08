#define GLEW_STATIC

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <Graphics/program.hpp>
#include <Graphics/objects.hpp>
#include <Input/handler.hpp>
#include <Geometry/triangle.hpp>

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

    auto triangle1 = Triangle(
        {0.2f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f},
        {-0.7f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f},
        {-0.25f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f});

    auto triangle2 = Triangle(
        {-0.2f, 0.5f, 0.0f},   {0.0f, 0.0f, 1.0f},
        { 0.7f, 0.5f, 0.0f},   {0.0f, 1.0f, 0.0f},
        { 0.25f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}); 

    auto triangle_shader = Program({
        {"src\\Shaders\\triangle.vert", GL_VERTEX_SHADER}, 
        {"src\\Shaders\\triangle.frag", GL_FRAGMENT_SHADER}});

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    InputHandler input_handler;

    bool running = true;
    while (running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    running = false;
                    break;

                case sf::Event::Resized:
                    glViewport(0, 0, event.size.width, event.size.height);
                    break;

                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::Escape)
                        running = false;
                    else
                        input_handler(event.key);
                    break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        triangle_shader.use();
        triangle1.draw();
        triangle2.draw();

        window.display();
    }
}