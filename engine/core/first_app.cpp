#include "first_app.hpp"

#include "keyboard_movement_controller.hpp"
#include "lve_camera.hpp"
#include "simple_render_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <array>
#include <chrono>
#include <cassert>
#include <stdexcept>

namespace lve {

FirstApp::FirstApp() { loadGameObjects(); }

FirstApp::~FirstApp() {}

void FirstApp::run() {
  SimpleRenderSystem simpleRenderSystem{lveDevice, lveRenderer.getSwapChainRenderPass()};
  LveCamera camera{};

  // position of test object
  camera.setViewTarget2d(glm::vec2(0.f,0.f), 0.f);
  
  auto viewerObject = LveGameObject::createGameObject( Camera );
  KeyboardMovementController cameraController{ };

  auto currentTime = std::chrono::high_resolution_clock::now();
 

  while (!lveWindow.shouldClose()) {
    glfwPollEvents();

    auto newTime = std::chrono::high_resolution_clock::now();
    auto frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
    currentTime = newTime;

    frameTime = glm::min(frameTime, 144.f);

    cameraController.move(lveWindow.getGLFWwindow(), frameTime, viewerObject);
    camera.setViewTarget2d(viewerObject.transform2d.position, viewerObject.transform2d.rotation);

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
  glm::vec2 offset{0.f,0.f};
  LveModel::Builder modelBuilder{};
  modelBuilder.verticies = { // list to construct from
      {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
      {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
      {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
      {{-0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
  };

  for (auto & v: modelBuilder.verticies){
    v.position += offset;
  }

  modelBuilder.indicies = {0,1,2, 0,3,2}; // performance optimizatin we choose from our verticies list and construct the triangles via indicies from it

  auto lveModel = std::make_shared<LveModel>(lveDevice, modelBuilder);

  auto quad = LveGameObject::createGameObject( Unit );
  quad.model = lveModel;
  quad.color = {.1f, .8f, .1f};
  quad.transform2d.position.x = 0.5f;
  quad.transform2d.position.y = 0.5f;
  quad.transform2d.scale = {0.6f, 0.6f};
  // triangle.transform2d.rotation = 90.f;

  gameObjects.push_back(std::move(quad));
}

}  // namespace lve
