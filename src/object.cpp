//
// Created by Oscar Jauffret on 17/06/2026.
//

#include "object.hpp"
#include <vector>

#include "config.hpp"
#include <iostream>

using namespace std;

void Object::computeVerticesAndIndices() {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    // vertices.push_back(x);
    // vertices.push_back(y);
    // vertices.push_back(z);

    for (int i = 0; i < config::render::angular_resolution; i++) {
        for (int j = 0; j < config::render::angular_resolution; j++) {
            float theta = static_cast<float>(i) / config::render::angular_resolution * config::pi * 2;
            //cout << "theta: " << theta << endl;
            float phi = static_cast<float>(j) / config::render::angular_resolution * config::pi * 2;
            float xp = x + radius * cos(phi) * cos(theta);
            float yp = y + radius * cos(phi) * sin(theta);
            float zp = z + radius * sin(phi);
            vertices.push_back(xp);
            vertices.push_back(yp);
            vertices.push_back(zp);
        }
    }
    // 2. Generate Indices (The "Stitching")
    for (int i = 0; i <= config::render::angular_resolution; i++) {
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


void Object::toShader(const Shader& shader) {
    shader.setVec4("object", glm::vec4(x, y, z ,radius));
}
