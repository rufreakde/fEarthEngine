#include "first_app.hpp"

#include "lve_camera.hpp"
#include "simple_render_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <array>
#include <cassert>
#include <stdexcept>

namespace lve {

FirstApp::FirstApp() { loadGameObjects(); }

FirstApp::~FirstApp() {}

void FirstApp::run() {
  SimpleRenderSystem simpleRenderSystem{lveDevice, lveRenderer.getSwapChainRenderPass()};
  LveCamera camera{};

  // position of test object
  camera.setViewTarget2d(glm::vec2(0.f,0.f));
  

  while (!lveWindow.shouldClose()) {
    glfwPollEvents();

    float aspect = lveRenderer.getAspectRatio();
    // // https://youtu.be/YO46x8fALzE?list=PL8327DO66nu9qYVKLDmdLW_84-yE4auCR&t=405
    camera.setOrthographicProjection(-aspect,aspect,-1,1,-1,1);

    if (auto commandBuffer = lveRenderer.beginFrame()) {
      lveRenderer.beginSwapChainRenderPass(commandBuffer);
      simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
      lveRenderer.endSwapChainRenderPass(commandBuffer);
      lveRenderer.endFrame();
    }
  }

  vkDeviceWaitIdle(lveDevice.device());
}

void FirstApp::loadGameObjects() {
  std::vector<LveModel::Vertex> vertices{
      {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
      {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
      {{0.f, 0.5f}, {0.0f, 0.0f, 1.0f}}};
  auto lveModel = std::make_shared<LveModel>(lveDevice, vertices);

  auto triangle = LveGameObject::createGameObject();
  triangle.model = lveModel;
  triangle.color = {.1f, .8f, .1f};
  triangle.transform2d.translation.x = 0.5f;
  triangle.transform2d.translation.y = 0.5f;
  triangle.transform2d.scale = {0.6f, 0.6f};
  // triangle.transform2d.rotation = 90.f;

  gameObjects.push_back(std::move(triangle));
}

}  // namespace lve
