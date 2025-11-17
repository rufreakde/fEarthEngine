#include "keyboard_movement_controller.hpp"
#include <limits>

namespace lve {

void KeyboardMovementController::move(GLFWwindow* window, float deltaTime, LveGameObject &gameObject){

    // --- 1. HANDLE ROTATION (Look) ---
    float rotationDelta = 0;
    if (glfwGetKey(window, keys.lookRight) == GLFW_PRESS){ rotationDelta += 1.f; };
    if (glfwGetKey(window, keys.lookLeft) == GLFW_PRESS){ rotationDelta -= 1.f; };

    // Update rotation and ensure it wraps correctly (optional, but good practice)
    gameObject.transform2d.rotation += lookSpeed * deltaTime * rotationDelta;
    gameObject.transform2d.rotation = glm::mod(gameObject.transform2d.rotation, glm::two_pi<float>());

    // --- 2. CALCULATE ORIENTATION VECTORS (2D) ---
    float yaw = gameObject.transform2d.rotation;
    
    // Forward direction (unit vector aligned with object's direction)
    // In 2D rotation (around Z), the forward vector is (cos(yaw), sin(yaw)).
    // Note: If 0 rotation means "Up" (positive Y), you might use (sin(yaw), cos(yaw)). 
    // Assuming 0 rotation means "Right" (positive X) for standard math rotation.
    // If your object starts facing UP (Positive Y) at rotation 0, swap sin and cos.
    const glm::vec2 forwardDir{cos(yaw), sin(yaw)}; 
    
    // Right direction (perpendicular to forwardDir)
    // This is simply the forward vector rotated 90 degrees clockwise (x, y) -> (y, -x)
    const glm::vec2 rightDir{forwardDir.y, -forwardDir.x};

    // --- 3. DETERMINE MOVEMENT DIRECTION ---
    glm::vec2 moveDir{0.f, 0.f};
    
    // Apply movement relative to the object's orientation
    if (glfwGetKey(window, keys.moveForward) == GLFW_PRESS) moveDir += forwardDir;
    if (glfwGetKey(window, keys.moveBackward) == GLFW_PRESS) moveDir -= forwardDir;
    if (glfwGetKey(window, keys.moveRight) == GLFW_PRESS) moveDir += rightDir;
    if (glfwGetKey(window, keys.moveLeft) == GLFW_PRESS) moveDir -= rightDir;

    // --- 4. APPLY TRANSLATION ---
    if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon()) {
        // Normalize the movement direction vector, multiply by speed and time
        gameObject.transform2d.translation += moveSpeed * deltaTime * glm::normalize(moveDir);
    }
}


}
