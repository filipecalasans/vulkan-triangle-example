#pragma once

#include "lve_game_object.h"
#include "lve_input_source.h"

namespace lve {
class KeyboardMovementController {
 public:

  struct KeyMappings {
    KeyNum moveLeft = KeyNum::A;
    KeyNum moveRight = KeyNum::D;
    KeyNum moveForward = KeyNum::W;
    KeyNum moveBackward = KeyNum::S;
    KeyNum moveUp = KeyNum::E;
    KeyNum moveDown = KeyNum::Q;
    KeyNum lookLeft = KeyNum::Left;
    KeyNum lookRight = KeyNum::Right;
    KeyNum lookUp = KeyNum::Up;
    KeyNum lookDown = KeyNum::Down;
    KeyNum resetView = KeyNum::Space;
  };

  void moveInPlaneXZ(LveInputSource& inputSource, float dt, LveGameObject& gameObject);

  KeyMappings keys{};
  float moveSpeed{3.f};
  float lookSpeed{1.5f};
};
}  // namespace lve