//
// Created by Oscar Jauffret on 17/06/2026.
//

#include "body.hpp"
#include <vector>

#include "config.hpp"
#include <iostream>
#include <numbers>

using namespace std;

void Body::computeVerticesAndIndices(glm::vec3 color) {
    normalizeRGB(color);
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i <= config::render::angular_resolution; i++) {
        for (int j = 0; j <= config::render::angular_resolution; j++) {
            float theta = static_cast<float>(i) / config::render::angular_resolution * numbers::pi * 2;
            float phi = static_cast<float>(j) / config::render::angular_resolution * numbers::pi * 2;
            float xp = renderRadius * cos(phi) * cos(theta);
            float yp = renderRadius * cos(phi) * sin(theta);
            float zp = renderRadius * sin(phi);
            vertices.push_back(xp);
            vertices.push_back(yp);
            vertices.push_back(zp);
            vertices.push_back(color[0]);
            vertices.push_back(color[1]);
            vertices.push_back(color[2]);
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

void Body::draw() const {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    Drawable::draw();
}

BodyType Body::getType() const { return type; }
double Body::getMass() const { return mass; }
glm::dvec3 Body::getPos() const { return pos; }
glm::dvec3 Body::getVel() const { return vel; }

void Body::setPos(glm::dvec3 pos) { this->pos = pos; }
void Body::setVel(glm::dvec3 vel) { this->vel = vel; }


void Body::update() {
    pos += vel * config::physics::dt;
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
