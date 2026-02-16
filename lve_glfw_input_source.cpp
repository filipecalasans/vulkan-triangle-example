#include "lve_glfw_input_source.h"
#include "lve_window.h"

namespace lve {

LveGlfwInputSource::LveGlfwInputSource(LveWindow& window)
    : LveInputSource(window), window(window) {}

LveGlfwInputSource::~LveGlfwInputSource() {}

void LveGlfwInputSource::pollEvents() {
  glfwPollEvents();
}

KeyState LveGlfwInputSource::getKeyState(KeyNum num) {
  auto* glfwWindow = static_cast<GLFWwindow*>(window.getNativeWindow());
  // Assumes that that KeyNum follows Glfw3 convention.
  const int state = glfwGetKey(glfwWindow, static_cast<int>(num));

  switch (state) {
    case GLFW_PRESS:
      return KeyState::Press;
    case GLFW_REPEAT:
      return KeyState::Repeat;
    default:
      return KeyState::Release;
  }
}

}  // namespace lve
