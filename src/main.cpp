//
// Created by Oscar Jauffret on 17/06/2026.
//

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
#include "celestialBody.hpp"
#include "config.hpp"
#include "spaceTime.hpp"
#include "objectUtils.hpp"

int main() {
    Window window(config::window::width, config::window::height, "Groovy Gravity");

    glfwSetInputMode(window.getHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    std::string dir = SHADER_DIR;
    Shader celestialBodyShader((dir + "/celestialBody.vert").c_str(), (dir + "/celestialBody.frag").c_str());
    Shader spaceTimeShader((dir + "/spaceTime.vert").c_str(), (dir + "/spaceTime.frag").c_str());

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

    CelestialBody sun(config::CelestialBodies::Sun, 10);
    CelestialBody earth(config::CelestialBodies::Earth, 10);

    earth.setVz(29290);
    SpaceTime spaceTime(200, 152e9 * 2.5);
    float lastFrame = 0.0f;
    bool  rHeldLastFrame = false;

    double hsqSunEarth = hsq(sun, earth);

    glm::mat4 model = glm::mat4(1.0f);

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
            spaceTimeShader.reload();
            celestialBodyShader.reload();
        }
        rHeldLastFrame = rHeld;

        window.clear(0.1f, 0.1f, 0.12f, 1.0f);  // clears color + depth by default

        orbit(sun, earth, hsqSunEarth);
        sun.update();
        earth.update();

        spaceTimeShader.use();
        spaceTimeShader.setMat4("uModel", model);
        glm::vec3 camPos = glm::vec3(scaleDistanceForRender(sun.getX()), scaleDistanceForRender(sun.getY()), scaleDistanceForRender(sun.getZ()));
        spaceTimeShader.setMat4("uView", camera.getViewMatrix(camPos));
        spaceTimeShader.setMat4("uProj", projection);

        auto sendObjectToSpaceTimeShader = [&spaceTimeShader](CelestialBody& body) {
            double rs = 2 * config::physics::G * body.getMass() / (config::physics::c * config::physics::c);
            spaceTimeShader.setFloat("rs", 5);  //TODO: figure out what to do with rs
            spaceTimeShader.setVec2("objectPos", glm::vec2(scaleDistanceForRender(body.getX()), scaleDistanceForRender(body.getY())));
        };
        sendObjectToSpaceTimeShader(sun);
        //spaceTime.draw();

        celestialBodyShader.use();
        celestialBodyShader.setMat4("uView", camera.getViewMatrix(camPos));
        celestialBodyShader.setMat4("uProj", projection);

        auto sendObjectToCBShader = [&celestialBodyShader](CelestialBody& body, glm::vec3 sunPosition, bool lightSource = false) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(
            scaleDistanceForRender(body.getX()),
            scaleDistanceForRender(body.getY()),
            scaleDistanceForRender(body.getZ())
        ));
            celestialBodyShader.setMat4("uModel", model);
            celestialBodyShader.setBool("lightSource", lightSource);
            celestialBodyShader.setVec3("sunPosition", sunPosition);
        };
        sendObjectToCBShader(sun, center(sun), true);
        sun.draw();
        sendObjectToCBShader(earth, center(sun));
        earth.draw();

        window.swapBuffers();
        window.pollEvents();
    }
    return 0;
}
