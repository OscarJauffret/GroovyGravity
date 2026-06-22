//
// Created by Oscar Jauffret on 17/06/2026.
//

#include <graphics/window.hpp>
#include <graphics/camera.hpp>
#include <graphics/shader.hpp>
#include "object.hpp"
#include "config.hpp"
#include "spaceTime.hpp"

int main() {
    Window window(config::window::width, config::window::height, "Groovy Gravity");

    // The library captures the cursor? No — that's the app's choice. Do it here.
    glfwSetInputMode(window.getHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    std::string dir = SHADER_DIR;
    Shader objectShader((dir + "/object.vert").c_str(), (dir + "/common.frag").c_str());
    Shader spaceTimeShader((dir + "/spaceTime.vert").c_str(), (dir + "/common.frag").c_str());

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

    // Mouse callback routed to the camera via the window user pointer.
    glfwSetWindowUserPointer(window.getHandle(), &camera);
    glfwSetCursorPosCallback(window.getHandle(),
        [](GLFWwindow* w, double x, double y) {
            auto* cam = static_cast<Camera*>(glfwGetWindowUserPointer(w));
            cam->processMouse(x, y);
        });

    float pos1[3] = {0.0f, 0.0f, 0.0f};
    float pos2[3] = {pos1[0] + 10, pos1[1], pos1[2]};
    float sunMass =  3.36648e+27;
    Object object0(sunMass, 5, pos1, {252, 229, 112});  // sun
    Object object1(1000, 2, pos2, {192, 200, 255});
    SpaceTime spaceTime(10, 10);
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
        //if (glfwGetKey(h, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera.moveDown(dt);

        // Hot-reload on a rising edge of R, so it fires once per press.
        bool rHeld = glfwGetKey(h, GLFW_KEY_R) == GLFW_PRESS;
        if (rHeld && !rHeldLastFrame) {
            spaceTimeShader.reload();
            objectShader.reload();
        }
        rHeldLastFrame = rHeld;

        window.clear(0.1f, 0.1f, 0.12f, 1.0f);  // clears color + depth by default

        spaceTimeShader.use();
        spaceTimeShader.setMat4("uModel", model);
        spaceTimeShader.setMat4("uView", camera.getViewMatrix());
        spaceTimeShader.setMat4("uProj", projection);

        auto sendObjectToSpaceTimeShader = [&spaceTimeShader](Object& object, int id) {
            cout << "mass: " << object.getMass() << endl;
            spaceTimeShader.setVec3("object[" + std::to_string(id) + "]", glm::vec3(object.getMass(), object.getX(), object.getZ()));
        };
        sendObjectToSpaceTimeShader(object0, 0);
        //sendObjectToSpaceTimeShader(object1, 1);
        spaceTime.draw();

        objectShader.use();
        objectShader.setMat4("uModel", model);
        objectShader.setMat4("uView", camera.getViewMatrix());
        objectShader.setMat4("uProj", projection);

        object0.draw();
        //object1.draw();

        window.swapBuffers();
        window.pollEvents();
    }
    return 0;
}
