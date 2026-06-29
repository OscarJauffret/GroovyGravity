//
// Created by Oscar Jauffret on 29/06/2026.
//

#include "universeRenderer.hpp"
#include <iostream>


using std::cerr;
using std::endl;
using std::cout;

unsigned long long UniverseRenderer::findBodyIndexThatWarpsSpaceTime(Universe& universe) const {
    unsigned long long count = 0;
    unsigned long long firstIdx = 0;

    for (int i = 0; i < universe.getBodies().size(); i++) {
        const Body& body = universe.getBodies()[i];
        if (body.getType() == BodyType::Star || body.getType() == BodyType::Blackhole) {
            if (count == 0) {
                firstIdx = i;
            }
            count++;
        }
    }
    if (count == 0) {
        cerr << "Warning: No warping body was found in the universe" << endl;
    } else if (count > 1) {
        cerr << "Warning: More than one warping body was found in the universe, defaulting to the one that comes first in the list of bodies in the Universe object" << endl;
    }

    return firstIdx;
}

void UniverseRenderer::render(Universe& universe, FixedCamera& camera, const glm::mat4& projection, SpaceTime& spaceTime) const {
    glm::mat4 model = glm::mat4(1.0f);
    const Body& warpingObject = universe.getBodies()[findBodyIndexThatWarpsSpaceTime(universe)];

    spaceTimeShader.use();
    spaceTimeShader.setMat4("uModel", model);
    glm::vec3 camPos = scaleDistanceForRender(warpingObject.getPos());
    spaceTimeShader.setMat4("uView", camera.getViewMatrix(camPos));
    spaceTimeShader.setMat4("uProj", projection);

    auto sendObjectToSpaceTimeShader = [this](const Body& body) {
        double rs = 2 * config::physics::G * body.getMass() / (config::physics::c * config::physics::c);
        spaceTimeShader.setFloat("rs", 5);  //TODO: figure out what to do with rs
        glm::vec3 pos = scaleDistanceForRender(body.getPos());
        spaceTimeShader.setVec2("objectPos", glm::vec2(pos.x, pos.y));
    };

    sendObjectToSpaceTimeShader(warpingObject);
    spaceTime.draw();


    bodyShader.use();
    bodyShader.setMat4("uView", camera.getViewMatrix(camPos));
    bodyShader.setMat4("uProj", projection);


    auto sendBodyToCBShader = [this, &warpingObject](const Body& body) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(scaleDistanceForRender(body.getPos())));
        bodyShader.setMat4("uModel", model);
        bodyShader.setBool("lightSource", body.getType() == BodyType::Star);
        bodyShader.setVec3("sunPosition", glm::vec3(scaleDistanceForRender(warpingObject.getPos())));
    };

    for (auto& b: universe.getBodies()) {
        sendBodyToCBShader(b);
        b.draw();
    }
}

void UniverseRenderer::reloadShaders() {
    spaceTimeShader.reload();
    bodyShader.reload();
}
