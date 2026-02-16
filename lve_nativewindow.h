#ifndef LVE_NATIVE_WINDOW
#define LVE_NATIVE_WINDOW

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

// vulkan headers
#include <vulkan/vulkan.h>

namespace lve {

class LveInputSource;

class LveNativeWindow {

public:

    LveNativeWindow(int w, int h, std::string name)  : width{w}, height{h}, windowName{name} {}
    virtual ~LveNativeWindow() {}

    LveNativeWindow(const LveNativeWindow&) = delete;
    LveNativeWindow &operator=(const LveNativeWindow&) = delete;
    
    virtual std::vector<const char*> getRequiredExtensions() = 0;
    virtual bool shouldClose() = 0;
    virtual void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) = 0;
    virtual void waitForEvents() = 0;
    virtual std::unique_ptr<LveInputSource> createInputSource() = 0;

    VkExtent2D getExtent() { return {static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height)}; }
    bool resized() const { return frameBufferResized; }
    void resetResized() { frameBufferResized = false; }
    void* getNativeWindow() const { return window; }
    

protected:

    int width;
    int height;
    bool frameBufferResized = false;

    std::string windowName;
    void* window = nullptr;
};

}

#endif
