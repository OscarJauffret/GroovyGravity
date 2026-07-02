//
// Created by Oscar Jauffret on 29/06/2026.
//

#include "bodyRenderer.hpp"
#include "numbers"


BodyRenderer::BodyRenderer() {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i <= config::render::angular_resolution; i++) {
        for (int j = 0; j <= config::render::angular_resolution; j++) {
            float theta = static_cast<float>(i) / config::render::angular_resolution * numbers::pi * 2;
            float phi = static_cast<float>(j) / config::render::angular_resolution * numbers::pi * 2;
            float xp = cos(phi) * cos(theta);
            float yp = cos(phi) * sin(theta);
            float zp = sin(phi);
            vertices.push_back(xp);
            vertices.push_back(yp);
            vertices.push_back(zp);
        }
    }

    for (int i = 0; i < config::render::angular_resolution; i++) {
        int k1 = i * (config::render::angular_resolution + 1);
        int k2 = k1 + config::render::angular_resolution + 1;
        for (int j = 0; j < config::render::angular_resolution; j++, k1++, k2++) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if (i != config::render::angular_resolution - 1) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
    indexCount = indices.size();
    setup(vertices, indices);
}

void BodyRenderer::draw() const {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    Drawable::draw();
}


ostream& operator<<(ostream& os, Body const& b) {
    os  << "---- Position ----" << endl
        << "X (real): " << b.getPos().x << ", (sim): " << scaleDistanceForRender(b.getPos().x) << endl
        << "Y (real): " << b.getPos().y << ", (sim): " << scaleDistanceForRender(b.getPos().y) << endl
        << "Z (real): " << b.getPos().z << ", (sim): " << scaleDistanceForRender(b.getPos().z) << endl
        << "---- Velocity ----" << endl
        << "Vx (real): " << b.getVel().x << ", (sim): " << scaleDistanceForRender(b.getVel().x) << endl
        << "Vy (real): " << b.getVel().y << ", (sim): " << scaleDistanceForRender(b.getVel().y) << endl
        << "Vz (real): " << b.getVel().z << ", (sim): " << scaleDistanceForRender(b.getVel().z) << endl;
    return os;
}