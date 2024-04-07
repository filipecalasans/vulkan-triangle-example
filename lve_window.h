#ifndef LVE_WINDOW
#define LVE_WINDOW

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

#include "lve_nativewindow.h"

namespace lve {

class LveWindow : public LveNativeWindow {

public:

    LveWindow(int w, int h, std::string name);
    virtual ~LveWindow();

    LveWindow(const LveWindow&) = delete;
    LveWindow &operator=(const LveWindow&) = delete;
    
    std::vector<const char*> getRequiredExtensions() override;
    bool shouldClose() override;
    void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) override;
    void waitForEvents() override;
    
private:

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    void initWindow();
};

}

#endif