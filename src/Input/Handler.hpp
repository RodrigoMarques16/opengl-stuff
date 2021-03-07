#pragma once

#include <SFML/Window/Event.hpp>

#include <functional>
#include <unordered_map>
#include <vector>

class InputHandler {
    using Key = sf::Keyboard::Key;
    using Callback = std::function<void()>;

    std::unordered_map<Key, Callback> callbacks = {
        {Key::Space, toggle_wireframe}};

    static inline const Callback toggle_wireframe = []() {
        static bool disabled = false;
        // GL_LINE = 0xB01, GL_FILL = 0xB02
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE + disabled);
        disabled = !disabled;
    };

   public:
    void operator()(sf::Event::KeyEvent e) {
        if (callbacks.contains(e.code))
            callbacks[e.code]();
    }
};