//
// Created by Oscar Jauffret on 17/06/2026.
//

#include <graphics/window.hpp>
#include <graphics/camera.hpp>
#include <graphics/shader.hpp>
#include "object.hpp"
#include "config.hpp"
#include "spaceTime.hpp"
#include "objectUtils.hpp"

int main() {
    Window window(config::window::width, config::window::height, "Groovy Gravity");

    // The library captures the cursor? No — that's the app's choice. Do it here.
    glfwSetInputMode(window.getHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    std::string dir = SHADER_DIR;
    Shader objectShader((dir + "/object.vert").c_str(), (dir + "/common.frag").c_str());
    Shader spaceTimeShader((dir + "/spaceTime.vert").c_str(), (dir + "/common.frag").c_str());

    Camera camera(glm::vec3(scaleDistanceForRender(config::CelestialBodies::Earth.pos[0]), 0.0f, 400.0f), 50.0f);

    // Mouse callback routed to the camera via the window user pointer.
    glfwSetWindowUserPointer(window.getHandle(), &camera);
    glfwSetCursorPosCallback(window.getHandle(),
        [](GLFWwindow* w, double x, double y) {
            auto* cam = static_cast<Camera*>(glfwGetWindowUserPointer(w));
            cam->processMouse(x, y);
        });

    Object sun(config::CelestialBodies::Sun, 10);  // sun
    Object earth(config::CelestialBodies::Earth, 5);

    earth.setVz(29290);
    earth.setVx(-150);
    SpaceTime spaceTime(200, config::CelestialBodies::Earth.pos[0] * 2.5);
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

        for (int i = 0; i < 2; i++) {
            for (int j = i; j < 2; j++) {
                orbit(sun, earth, hsqSunEarth);
                sun.update();
                earth.update();
                //cout << "Sun:\n" << sun << endl;
                //cout << "Earth:\n" << earth << endl;

                spaceTimeShader.use();
                spaceTimeShader.setMat4("uModel", model);
                spaceTimeShader.setMat4("uView", camera.getViewMatrix());
                spaceTimeShader.setMat4("uProj", projection);

                auto sendObjectToSpaceTimeShader = [&spaceTimeShader](Object& object, int id) {
                    spaceTimeShader.setVec3("objects[" + std::to_string(id) + "]", glm::vec3(object.getMass(), scaleDistanceForRender(object.getX()), scaleDistanceForRender(object.getZ())));
                };
                sendObjectToSpaceTimeShader(sun, 0);
                //spaceTime.draw();

                auto sendObjectToObjectShader = [&objectShader](Object& object, int id) {
                    objectShader.setVec3("objectPositions[" + std::to_string(id) + "]", glm::vec3(
                        scaleDistanceForRender(object.getX()), scaleDistanceForRender(object.getY()), scaleDistanceForRender(object.getZ())));
                };
                objectShader.use();
                objectShader.setMat4("uModel", model);
                objectShader.setMat4("uView", camera.getViewMatrix());
                objectShader.setMat4("uProj", projection);
                sendObjectToObjectShader(sun, 0);
                sendObjectToObjectShader(earth, 1);

                objectShader.setInt("objectIndex", 0);
                sun.draw();
                objectShader.setInt("objectIndex", 1);
                earth.draw();
            }}

        window.swapBuffers();
        window.pollEvents();
    }
    return 0;
}
