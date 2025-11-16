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
  float rotation = 0.0f;              // Rotation angle (around Z-axis, in radians)
  // Returns the combined 3x3 transformation matrix (Model Matrix).
  // The matrix composition order is: Translation * Rotation_Pivot * Scale
  glm::mat4 mat4() {

    // ommit Z
    auto rot = glm::vec3{0.f, 0.f, rotation};
    auto sca = glm::vec3( scale, 0);

    const float c3 = glm::cos(rot.z);
    const float s3 = glm::sin(rot.z);
    const float c2 = glm::cos(rot.x);
    const float s2 = glm::sin(rot.x);
    const float c1 = glm::cos(rot.y);
    const float s1 = glm::sin(rot.y);
    return glm::mat4{
        {
            scale.x * (c1 * c3 + s1 * s2 * s3),
            scale.x * (c2 * s3),
            scale.x * (c1 * s2 * s3 - c3 * s1),
            0.0f,
        },
        {
            scale.y * (c3 * s1 * s2 - c1 * s3),
            scale.y * (c2 * c3),
            scale.y * (c1 * c3 * s2 + s1 * s3),
            0.0f,
        },
        {
            sca.z * (c2 * s1),
            sca.z * (-s2),
            sca.z * (c1 * c2),
            0.0f,
        },
        {translation.x, -translation.y, 0.f, 1.0f}}; // invert translation.y we want Y to be positive top and negative bottom just to avoid brainfucks
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
