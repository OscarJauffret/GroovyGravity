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
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);

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
        // indices.push_back(0);
        // indices.push_back(i+1);
        // indices.push_back(i+2);
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
    // indices.push_back(0);
    // indices.push_back(20);
    // indices.push_back(1);
    //
    // vertices = {
    //     0.5, 0.5, 0.0,   // top right
    //     0.5, -0.5, -0.0,  // bottom right
    //     -0.5, 0.5, 0.0,    // top left
    //     -0.5, -0.5, 0.0   // bottom left
    // };
    //
    // indices = {
    //     0, 1, 2,  // first triangle
    //     2, 3, 1   // second triangle
    // };

    index_count = indices.size();
    cout << "Vertices created" << endl;
    setup(vertices, indices);
}


void Object::setup(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO); // use current VAO for all subsequent calls

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Layout 0: Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    cout << "Set up" << endl;

}

void Object::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
}

Object::~Object() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Object::toShader(const Shader& shader) {
    shader.setVec4("object", glm::vec4(x, y, z ,radius));
}
