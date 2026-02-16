#pragma once

#include "lve_input_source.h"

namespace lve {

class LveWindow;

class LveGlfwInputSource : public LveInputSource {
 public:
  explicit LveGlfwInputSource(LveWindow& window);
  ~LveGlfwInputSource() override;

  void pollEvents() override;
  KeyState getKeyState(KeyNum num) override;

 private:
  LveWindow& window;
};

}  // namespace lve
