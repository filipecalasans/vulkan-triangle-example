#ifndef LVE_WINDOW
#define LVE_WINDOW

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace lve {

class LveWindow {

public:

    LveWindow(int w, int h, std::string name);
    ~LveWindow();

    LveWindow(const LveWindow&) = delete;
    LveWindow &operator=(const LveWindow&) = delete;
    
    bool shouldClose();
    void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);
    VkExtent2D getExtent() { return {static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height)}; }

private:

    void initWindow();


    const int width;
    const int height;

    std::string windowName;
    GLFWwindow *window;
};

}

#endif