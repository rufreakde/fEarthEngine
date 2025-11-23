#include "keyboard_movement_controller.hpp"
#include <limits>
#include <iostream>

namespace lve {

void KeyboardMovementController::move(GLFWwindow* window, float deltaTime, LveGameObject &gameObject){

    // --- 1. HANDLE ROTATION (Look) ---
    // Note I dont think there will be anything that rotates later on. But maybe it is necessary for something so I would not rule it out and keep the code here as is
    if ( gameObject.getType() == Misc ) {
        float rotationDelta = 0;
        if (glfwGetKey(window, keys.lookRight) == GLFW_PRESS){ rotationDelta += 1.f; };
        if (glfwGetKey(window, keys.lookLeft) == GLFW_PRESS){ rotationDelta -= 1.f; };

        // Update rotation and ensure it wraps correctly (optional, but good practice)
        gameObject.transform2d.rotation += lookSpeed * deltaTime * rotationDelta;
        gameObject.transform2d.rotation = glm::mod(gameObject.transform2d.rotation, glm::two_pi<float>());

        // --- 2. CALCULATE ORIENTATION VECTORS (2D) ---
        float yaw = gameObject.transform2d.rotation;
    }
    
    // Forward direction (unit vector aligned with object's direction)
    // In 2D rotation (around Z), the forward vector is (cos(yaw), sin(yaw)).
    // Note: If 0 rotation means "Up" (positive Y), you might use (sin(yaw), cos(yaw)). 
    // Assuming 0 rotation means "Right" (positive X) for standard math rotation.
    // If your object starts facing UP (Positive Y) at rotation 0, swap sin and cos.
    const glm::vec2 upDir{0, 1.f};
    const glm::vec2 downDir{0, -1.f}; 
    const glm::vec2 leftDir{-1.f, 0}; 
    const glm::vec2 rightDir{1.f, 0}; 

    // --- 3. DETERMINE MOVEMENT DIRECTION ---
    glm::vec2 moveDir{0.f, 0.f};
    
    // Apply movement relative to the object's orientation
    // this should be world direction on screen
    // top screen +y and left screen -x
    if (glfwGetKey(window, keys.moveUp) == GLFW_PRESS) moveDir += upDir;
    if (glfwGetKey(window, keys.moveDown) == GLFW_PRESS) moveDir += downDir;
    if (glfwGetKey(window, keys.moveRight) == GLFW_PRESS) moveDir += rightDir;
    if (glfwGetKey(window, keys.moveLeft) == GLFW_PRESS) moveDir += leftDir;

    // --- 4. APPLY TRANSLATION ---
    if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon()) {
        // Normalize the movement direction vector, multiply by speed and time
        glm::vec2 normalizedDirection = deltaTime * glm::normalize(moveDir);
        gameObject.transform2d.position += moveSpeed * normalizedDirection;
        std::cout << "Position: (" << gameObject.transform2d.position.x << ", " << gameObject.transform2d.position.y << " - Direction: (" << normalizedDirection.x << "," << normalizedDirection.y << ")\n";

    }
}


}
