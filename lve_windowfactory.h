#ifndef LVE_WINDOW_FACTORY
#define LVE_WINDOW_FACTORY

#include <memory>
#include <string>

#if defined(GLFW_XPLAT_DESKTOP)
#include "lve_window.h"
#endif

namespace lve {

std::unique_ptr<LveNativeWindow> createNativeWindow(int w, int h, std::string name) {
    #if defined(GLFW_XPLAT_DESKTOP)
        return std::make_unique<LveWindow>(w, h, std::move(name));
    #elif defined(ANDROID)
        #error "Android is not supported yet! Coming soon!"
    #else
        #error "Window System Not Defined!"
    #endif
    return nullptr;
}

}

#endif