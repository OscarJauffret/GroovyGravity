//
// Created by Oscar Jauffret on 17/06/2026.
//

#include "object.hpp"
#include <vector>

#include "config.hpp"
#include <iostream>
#include <numbers>

using namespace std;

void Object::computeVerticesAndIndices(glm::vec3 color) {
    normalizeRGB(color);
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    double renderRadius = scaleRadiusForRender(radius);
    double renderX = scaleDistanceForRender(x);
    double renderY = scaleDistanceForRender(y);
    double renderZ = scaleDistanceForRender(z);

    for (int i = 0; i <= config::render::angular_resolution; i++) {
        for (int j = 0; j <= config::render::angular_resolution; j++) {
            float theta = static_cast<float>(i) / config::render::angular_resolution * numbers::pi * 2;
            float phi = static_cast<float>(j) / config::render::angular_resolution * numbers::pi * 2;
            float xp = renderX + renderRadius * cos(phi) * cos(theta);
            float yp = renderY + renderRadius * cos(phi) * sin(theta);
            float zp = renderZ + renderRadius * sin(phi);
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

void Object::draw() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    Drawable::draw();
}

double Object::getMass() const{
    return mass;
}

double Object::getX() const {
    return x;
}

double Object::getY() const {
    return y;
}

double Object::getZ() const {
    return z;
}

double Object::getVx() const {
    return vx;
}


double Object::getVy() const {
    return vy;
}


double Object::getVz() const {
    return vz;
}

void Object::setX(double tx) { x = tx;}
void Object::setY(double ty) { y = ty;}
void Object::setZ(double tz) { z = tz;}
void Object::setVx(double tvx) { vx = tvx;}
void Object::setVy(double tvy) { vy = tvy;}
void Object::setVz(double tvz) { vz = tvz;}

void Object::update() {
    setX(getX() + getVx() * config::physics::dt);
    setY(getY() + getVy() * config::physics::dt);
    setZ(getZ() + getVz() * config::physics::dt);
}

ostream& operator<<(ostream& os, Object const& o) {
    os  << "---- Position ----" << endl
        << "X (real): " << o.getX() << ", (sim): " << scaleDistanceForRender(o.getX()) << endl
        << "Y (real): " << o.getY() << ", (sim): " << scaleDistanceForRender(o.getY()) << endl
        << "Z (real): " << o.getZ() << ", (sim): " << scaleDistanceForRender(o.getZ()) << endl
        << "---- Velocity ----" << endl
        << "Vx (real): " << o.getVx() << ", (sim): " << scaleDistanceForRender(o.getVx()) << endl
        << "Vy (real): " << o.getVy() << ", (sim): " << scaleDistanceForRender(o.getVy()) << endl
        << "Vz (real): " << o.getVz() << ", (sim): " << scaleDistanceForRender(o.getVz()) << endl;
    return os;
}
