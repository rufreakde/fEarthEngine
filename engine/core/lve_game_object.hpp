#pragma once

#include "lve_model.hpp"

// libs
#include <glm/gtc/matrix_transform.hpp>

// std
#include <memory>

namespace lve {

struct Transform2dComponent {
  glm::vec2 translation{};  // (position offset)
  glm::vec2 scale{1.f, 1.f};
  float rotation;

  // Deprecated: Using mat3() is preferred for combining translation/scale/rotation.
  // glm::mat2 mat2() {
  //   const float s = glm::sin(rotation);
  //   const float c = glm::cos(rotation);
  //   glm::mat2 rotMatrix{{c, s}, {-s, c}};

  //   glm::mat2 scaleMat{{scale.x, .0f}, {.0f, scale.y}};
  //   return rotMatrix * scaleMat;
  // }

  // Returns a 3x3 transformation matrix for 2D transformations (Homogeneous Coordinates).
  // The matrix combines rotation, scale, and translation.
  glm::mat3 mat3() const {
    // 1. Calculate sine and cosine of the single Z-axis rotation
    const float s = glm::sin(rotation);
    const float c = glm::cos(rotation);
    
    // 2. Initialize the 3x3 identity matrix
    glm::mat3 result{1.f};
    
    // 3. Combine Rotation and Scaling (R * S) and place into the top-left 2x2 part.
    // Order: Scale is applied first, then rotation.
    
    // Column 0 (X-axis vector: Rotated and Scaled X)
    result[0][0] = c * scale.x;
    result[0][1] = s * scale.x;
    // result[0][2] = 0.f; // (Already 0 from initialization)
    
    // Column 1 (Y-axis vector: Rotated and Scaled Y)
    result[1][0] = -s * scale.y;
    result[1][1] = c * scale.y;
    // result[1][2] = 0.f; // (Already 0 from initialization)

    // 4. Insert Translation into the third column (the homogeneous coordinate vector).
    // Column 2 (Translation vector)
    result[2][0] = translation.x;
    result[2][1] = translation.y;
    // result[2][2] = 1.f; // (Already 1 from initialization)

    return result;
  }
};

class LveGameObject {
 public:
  using id_t = unsigned int;

  static LveGameObject createGameObject() {
    static id_t currentId = 0;
    return LveGameObject{currentId++};
  }

  LveGameObject(const LveGameObject &) = delete;
  LveGameObject &operator=(const LveGameObject &) = delete;
  LveGameObject(LveGameObject &&) = default;
  LveGameObject &operator=(LveGameObject &&) = default;

  id_t getId() { return id; }

  std::shared_ptr<LveModel> model{};
  glm::vec3 color{};
  Transform2dComponent transform2d{};

 private:
  LveGameObject(id_t objId) : id{objId} {}

  id_t id;
};
}  // namespace lve
