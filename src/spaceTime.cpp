//
// Created by Oscar Jauffret on 17/06/2026.
//

#include "spaceTime.hpp"

SpaceTime::SpaceTime(int resolution, float size, glm::vec3 color) {
    normalizeRGB(color);
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    // 1. Generate Vertices
    for (int i = 0; i <= resolution; i++) {
        for (int j = 0; j <= resolution; j++) {
            float x = (float)i / (float)resolution * size - size/2.0f;
            float z = (float)j / (float)resolution * size - size/2.0f;

            vertices.push_back(x);      // X
            vertices.push_back(0.0f); // Y
            vertices.push_back(z);      // Z
            vertices.push_back(color[0]);
            vertices.push_back(color[1]);
            vertices.push_back(color[2]);
        }
    }

    // 2. Generate Indices (The "Stitching")
    for (int i = 0; i < resolution; i++) {
        for (int j = 0; j < resolution; j++) {
            int row1 = i * (resolution + 1) + j;
            int row2 = (i + 1) * (resolution + 1) + j;

            // Triangle 1
            indices.push_back(row1);
            indices.push_back(row1 + 1);
            indices.push_back(row2);

            // Triangle 2
            indices.push_back(row1 + 1);
            indices.push_back(row2 + 1);
            indices.push_back(row2);
        }
    }
    indexCount = indices.size();
    setup(vertices, indices);
}

void SpaceTime::draw() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Drawable::draw();
}