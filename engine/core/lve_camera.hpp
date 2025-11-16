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

            // --- CHANGE 1: Return a mat3 projection matrix ---
            const glm::mat4& getProjection() const {return projectionMatrix; }

        private:
            // --- CHANGE 2: Store a mat3 projection matrix ---
            glm::mat4 projectionMatrix{1.f};
    };
}