#include "keyboard_movement_controller.h"

// std
#include <limits>

namespace lve {

void KeyboardMovementController::moveInPlaneXZ(
    LveInputSource& inputSource, float dt, LveGameObject& gameObject) {
  glm::vec3 rotate{0};
  if (inputSource.getKeyState(keys.lookRight) == KeyState::Press) rotate.y += 1.f;
  if (inputSource.getKeyState(keys.lookLeft) == KeyState::Press) rotate.y -= 1.f;
  
  if (inputSource.getKeyState(keys.lookUp) == KeyState::Press) rotate.x += 1.f;
  if (inputSource.getKeyState(keys.lookDown) == KeyState::Press) rotate.x -= 1.f;

  if (glm::dot(rotate, rotate) > std::numeric_limits<float>::epsilon()) {
    gameObject.transform.rotation += lookSpeed * dt * glm::normalize(rotate);
  }

  // limit pitch values between about +/- 85ish degrees
  gameObject.transform.rotation.x = glm::clamp(gameObject.transform.rotation.x, -1.5f, 1.5f);
  gameObject.transform.rotation.y = glm::mod(gameObject.transform.rotation.y, glm::two_pi<float>());

  float yaw = gameObject.transform.rotation.y;
  const glm::vec3 forwardDir{sin(yaw), 0.f, cos(yaw)};
  const glm::vec3 rightDir{forwardDir.z, 0.f, -forwardDir.x};
  const glm::vec3 upDir{0.f, -1.f, 0.f};

  glm::vec3 moveDir{0.f};


  if (inputSource.getKeyState(keys.moveForward) == KeyState::Press) moveDir += forwardDir;
  if (inputSource.getKeyState(keys.moveBackward) == KeyState::Press) moveDir -= forwardDir;
  if (inputSource.getKeyState(keys.moveRight) == KeyState::Press) moveDir += rightDir;
  if (inputSource.getKeyState(keys.moveLeft) == KeyState::Press) moveDir -= rightDir;
  if (inputSource.getKeyState(keys.moveUp) == KeyState::Press) moveDir += upDir;
  if (inputSource.getKeyState(keys.moveDown) == KeyState::Press) moveDir -= upDir;

  if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon()) {
    gameObject.transform.translation += moveSpeed * dt * glm::normalize(moveDir);
  }

  if (inputSource.getKeyState(keys.resetView) == KeyState::Press) {
    gameObject.transform.translation = glm::vec3{0.5f, 0.f, 0.5f};
    gameObject.transform.rotation = glm::vec3{0.0f, 0.0f, 0.0f};
  }
}
}  // namespace lve