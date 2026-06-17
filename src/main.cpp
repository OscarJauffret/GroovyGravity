//
// Created by Oscar Jauffret on 17/06/2026.
//

#include <graphics/window.hpp>
#include <graphics/camera.hpp>
#include <graphics/shader.hpp>
#include <object.hpp>

#include "config.hpp"
#include "spaceTime.hpp"

int main() {
    Window window(config::window::width, config::window::height, "Groovy Gravity");

    // The library captures the cursor? No — that's the app's choice. Do it here.
    glfwSetInputMode(window.getHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    std::string dir = SHADER_DIR;
    Shader shader((dir + "/gravity.vert").c_str(), (dir + "/gravity.frag").c_str());

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

    // Mouse callback routed to the camera via the window user pointer.
    glfwSetWindowUserPointer(window.getHandle(), &camera);
    glfwSetCursorPosCallback(window.getHandle(),
        [](GLFWwindow* w, double x, double y) {
            auto* cam = static_cast<Camera*>(glfwGetWindowUserPointer(w));
            cam->processMouse(x, y);
        });

    float pos[3] = {0.0f, 0.0f, 0.0f};
    Object object(100, 0.5, pos);
    SpaceTime spaceTime(100, 200);
    float lastFrame = 0.0f;
    bool  rHeldLastFrame = false;

    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        static_cast<float>(config::window::width) / static_cast<float>(config::window::height),
        0.1f,
        100.0f
    );

    while (!window.shouldClose()) {
        float now = static_cast<float>(glfwGetTime());
        float dt  = now - lastFrame;
        lastFrame = now;

        GLFWwindow* h = window.getHandle();
        if (glfwGetKey(h, GLFW_KEY_W) == GLFW_PRESS) camera.moveForward(dt);
        if (glfwGetKey(h, GLFW_KEY_S) == GLFW_PRESS) camera.moveBackward(dt);
        if (glfwGetKey(h, GLFW_KEY_A) == GLFW_PRESS) camera.moveLeft(dt);
        if (glfwGetKey(h, GLFW_KEY_D) == GLFW_PRESS) camera.moveRight(dt);
        if (glfwGetKey(h, GLFW_KEY_SPACE) == GLFW_PRESS) camera.moveUp(dt);
        if (glfwGetKey(h, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera.moveDown(dt);

        // Hot-reload on a rising edge of R, so it fires once per press.
        bool rHeld = glfwGetKey(h, GLFW_KEY_R) == GLFW_PRESS;
        if (rHeld && !rHeldLastFrame) shader.reload();
        rHeldLastFrame = rHeld;

        window.clear(0.1f, 0.1f, 0.12f, 1.0f);  // clears color + depth by default

        shader.use();
        shader.setMat4("uModel", model);
        shader.setMat4("uView", camera.getViewMatrix());
        shader.setMat4("uProj", projection);

        //object.toShader(shader);
        spaceTime.draw();
        object.draw();

        window.swapBuffers();
        window.pollEvents();
    }
    return 0;
}
