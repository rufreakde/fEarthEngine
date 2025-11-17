#pragma once

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace lve{

    class LveCamera{
        public:
            // We still need near/far in the signature even if we ignore them, 
            // as the function is often expected to take them.
            void setOrthographicProjection(float left, float right, float top, float bottom, float near, float far);

            void setViewTarget2d(glm::vec2 position, float rotation);

            // --- CHANGE 1: Return a mat3 projection matrix ---
            const glm::mat4& getProjection() const {return projectionMatrix; }
            const glm::mat4& getView() const {return viewMatrix; }

        private:
            // --- CHANGE 2: Store a mat3 projection matrix ---
            glm::mat4 projectionMatrix{1.f};
            glm::mat4 viewMatrix{1.f};

            // deprecated
            void setViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up = glm::vec3{0.f,-1.f,0.f});
            // target a position directly
            void setViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up = glm::vec3{0.f,-1.f,0.f});
            // deprecated
            void setViewEuler(glm::vec3 position, glm::vec3 rotation);
    };
}