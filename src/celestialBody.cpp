//
// Created by Oscar Jauffret on 17/06/2026.
//

#include "celestialBody.hpp"
#include <vector>

#include "config.hpp"
#include <iostream>
#include <numbers>

using namespace std;

void CelestialBody::computeVerticesAndIndices(glm::vec3 color) {
    normalizeRGB(color);
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    double renderX = scaleDistanceForRender(x);
    double renderY = scaleDistanceForRender(y);
    double renderZ = scaleDistanceForRender(z);

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

void CelestialBody::draw() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    Drawable::draw();
}

double CelestialBody::getMass() const { return mass; }
double CelestialBody::getX() const { return x; }
double CelestialBody::getY() const { return y; }
double CelestialBody::getZ() const { return z; }
double CelestialBody::getVx() const { return vx; }
double CelestialBody::getVy() const { return vy; }
double CelestialBody::getVz() const { return vz; }

void CelestialBody::setX(double tx) { x = tx; }
void CelestialBody::setY(double ty) { y = ty; }
void CelestialBody::setZ(double tz) { z = tz; }
void CelestialBody::setVx(double tvx) { vx = tvx; }
void CelestialBody::setVy(double tvy) { vy = tvy; }
void CelestialBody::setVz(double tvz) { vz = tvz; }

void CelestialBody::update() {
    setX(getX() + getVx() * config::physics::dt);
    setY(getY() + getVy() * config::physics::dt);
    setZ(getZ() + getVz() * config::physics::dt);
}

ostream& operator<<(ostream& os, CelestialBody const& b) {
    os  << "---- Position ----" << endl
        << "X (real): " << b.getX() << ", (sim): " << scaleDistanceForRender(b.getX()) << endl
        << "Y (real): " << b.getY() << ", (sim): " << scaleDistanceForRender(b.getY()) << endl
        << "Z (real): " << b.getZ() << ", (sim): " << scaleDistanceForRender(b.getZ()) << endl
        << "---- Velocity ----" << endl
        << "Vx (real): " << b.getVx() << ", (sim): " << scaleDistanceForRender(b.getVx()) << endl
        << "Vy (real): " << b.getVy() << ", (sim): " << scaleDistanceForRender(b.getVy()) << endl
        << "Vz (real): " << b.getVz() << ", (sim): " << scaleDistanceForRender(b.getVz()) << endl;
    return os;
}
