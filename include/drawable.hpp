//
// Created by Oscar Jauffret on 17/06/2026.
//

#ifndef GROOVYGRAVITY_DRAWABLE_HPP
#define GROOVYGRAVITY_DRAWABLE_HPP
#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <glm/vec4.hpp>
#include "utils.hpp"

using namespace std;

class Drawable {
protected:
    unsigned int VAO, VBO, EBO;
    unsigned int indexCount;

    /**
     * Takes a vector of vertices and a vector of indices and sets them up for openGL to use. The function initializes
     * buffers to store the arrays, and puts them into locations that are accessible for shaders.
     *
     * The function expects that each vertex has 6 components: 3 posistions (x, y, z) and then 3 for color
     * @param vertices Vector of vertices to set up in a VertexArray
     * @param indices Vector of indices to use with the vertices
     */
    void setup(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO); // use current VAO for all subsequent calls

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        int stride = 6;
        int positionSize = 3;
        // Layout 0: Position
        glVertexAttribPointer(0, positionSize, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Layout 1: color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float),
                              (void*)(positionSize * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

public:
    /**
     * Bind the vertex array to start using it
     */
    virtual void draw() const {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    }

    /**
     * Cleans the memory
     */
    ~Drawable() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
};

#endif //GROOVYGRAVITY_DRAWABLE_HPP
