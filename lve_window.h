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
    bool resized() const { return frameBufferResized; }
    void resetResized() { frameBufferResized = false; }
    GLFWwindow *getGLFWwindow() const { return window; }

private:

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    void initWindow();


    int width;
    int height;
    bool frameBufferResized = false;

    std::string windowName;
    GLFWwindow *window;
};

}

#endif