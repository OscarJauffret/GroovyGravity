//
// Created by Oscar Jauffret on 17/06/2026.
//

#include "bodyRenderer.hpp"
#include "universeRenderer.hpp"
#if defined(__ARM_NEON) || defined(__aarch64__)
// For Apple Silicon / ARM64
__attribute__((constructor)) static void __enable_ftz_daz(void) {
    unsigned long long fpcr;
    // Read the current Floating-Point Control Register
    __asm__ __volatile__("mrs %0, fpcr" : "=r"(fpcr));

    // Set Bit 24 (FZ - Flush-to-Zero)
    // Set Bit 27 (FZ16 - Half-precision Flush-to-Zero if applicable)
    fpcr |= (1ULL << 24);

    // Write back to the register
    __asm__ __volatile__("msr fpcr, %0" : : "r"(fpcr));
}
#elif defined(__x86_64__) || defined(_M_X64)
// Fallback for Intel/AMD machines
#include <xmmintrin.h>
#include <pmmintrin.h>
__attribute__((constructor)) static void __enable_ftz_daz(void) {
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
}
#endif

#include <graphics/window.hpp>
#include <graphics/fixedCamera.hpp>
#include <graphics/shader.hpp>
#include "body.hpp"
#include "config.hpp"
#include "spaceTime.hpp"
#include "bodyUtils.hpp"
#include "universe.hpp"
#include "presets.hpp"

int main() {
    Window window(config::window::width, config::window::height, "Groovy Gravity");

    glfwSetInputMode(window.getHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    FixedCamera camera(300, glm::vec3(0.0f, 0.0f, 0.0f), numbers::pi/4);

    // Mouse callback routed to the camera via the window user pointer.
    glfwSetWindowUserPointer(window.getHandle(), &camera);
    glfwSetCursorPosCallback(window.getHandle(),
        [](GLFWwindow* w, double x, double y) {
            auto* cam = static_cast<FixedCamera*>(glfwGetWindowUserPointer(w));
            cam->processMouse(x, y);
        });


    glfwSetScrollCallback(window.getHandle(),
        [](GLFWwindow* w, double xoffset, double yoffset){
            auto* cam = static_cast<FixedCamera*>(glfwGetWindowUserPointer(w));
            float d = cam->distance;
            d -= (float)yoffset;
            if (d < 30.0f) d = 30.0f;
            if (d > 500.0f) d = 500.0f;
            cam->setDistance(d);
    });

    Universe universe;
    universe.addBody(presets::Sun());
    universe.addBody(presets::Earth());

    UniverseRenderer universeRenderer(SHADER_DIR);

    SpaceTime spaceTime(200, 152e9 * 2.5);
    float lastFrame = 0.0f;
    bool  rHeldLastFrame = false;

    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        static_cast<float>(config::window::width) / static_cast<float>(config::window::height),
        0.1f,
        1000.0f
    );

    while (!window.shouldClose()) {
        float now = static_cast<float>(glfwGetTime());
        float dt  = now - lastFrame;
        lastFrame = now;
        GLFWwindow* h = window.getHandle();

        bool rHeld = glfwGetKey(h, GLFW_KEY_R) == GLFW_PRESS;
        if (rHeld && !rHeldLastFrame) {
            universeRenderer.reloadShaders();
        }
        rHeldLastFrame = rHeld;

        window.clear(0.1f, 0.1f, 0.12f, 1.0f);  // clears color + depth by default

        universe.update();
        universeRenderer.render(universe, camera, projection, spaceTime);


        window.swapBuffers();
        window.pollEvents();
    }
    return 0;
}
