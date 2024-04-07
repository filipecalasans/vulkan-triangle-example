#pragma once

#include "lve_device.h"
#include "lve_game_object.h"
#include "lve_render.h"
#include "lve_nativewindow.h"

// vulkan headers
#include <vulkan/vulkan.h>

//std
#include <cassert>
#include <memory>
#include <vector>

namespace lve {

class FirstApp
{
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    FirstApp();
    ~FirstApp();

    FirstApp(const FirstApp&) = delete;
    FirstApp &operator=(const FirstApp&) = delete;

    void run();

private:

    void loadGameObjects();
    void createSyncObjects();

    std::unique_ptr<LveNativeWindow> lveWindow; //{WIDTH, HEIGHT, "Hello Vulkan"};
    
    // LveDevice lveDevice{lveWindow};
    // LveRenderer lveRenderer{lveWindow, lveDevice};

    LveDevice lveDevice;
    LveRenderer lveRenderer;
 
    std::vector<LveGameObject> gameObjects;
};

}