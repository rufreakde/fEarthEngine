#pragma once

#include "lve_game_object.hpp"
#include "lve_window.hpp"

namespace lve {

    class KeyboardMovementController{


        public:
            struct KeyMappings {
                int moveLeft = GLFW_KEY_A;
                int moveRight = GLFW_KEY_D;
                int moveUp = GLFW_KEY_W;
                int moveDown = GLFW_KEY_S;
                int lookLeft = GLFW_KEY_LEFT;
                int lookRight = GLFW_KEY_RIGHT;
            };



            void move(GLFWwindow* window, float deltaTime, LveGameObject &gameObject);

        KeyMappings keys{};
        float moveSpeed{3.f};
        float lookSpeed{1.5f};
    };
}