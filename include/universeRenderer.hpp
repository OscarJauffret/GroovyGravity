//
// Created by Oscar Jauffret on 29/06/2026.
//

#ifndef GROOVYGRAVITY_UNIVERSERENDERER_HPP
#define GROOVYGRAVITY_UNIVERSERENDERER_HPP

#include "bodyRenderer.hpp"
#include "universe.hpp"
#include "graphics/fixedCamera.hpp"
#include "graphics/shader.hpp"
#include "spaceTime.hpp"

class UniverseRenderer {
private:
    Shader bodyShader;
    Shader spaceTimeShader;
    BodyRenderer bodyRenderer;

    unsigned long long findBodyIndexThatWarpsSpaceTime(Universe& universe) const;
public:

    UniverseRenderer(const std::string& shaderDir)
        : bodyShader((shaderDir + "/body.vert").c_str(), (shaderDir + "/body.frag").c_str()),
          spaceTimeShader((shaderDir + "/spaceTime.vert").c_str(), (shaderDir + "/spaceTime.frag").c_str()) {}

    void render(Universe& universe, FixedCamera& camera, const glm::mat4& projection, SpaceTime& spaceTime) const;

    void reloadShaders();
};


#endif //GROOVYGRAVITY_UNIVERSERENDERER_HPP
