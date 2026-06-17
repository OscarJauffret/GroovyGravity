//
// Created by Oscar Jauffret on 17/06/2026.
//

#ifndef GROOVYGRAVITY_OBJECT_HPP
#define GROOVYGRAVITY_OBJECT_HPP
#include <vector>
#include <graphics/shader.hpp>
#include <GL/glew.h>

struct Object {
private:
    float mass;
    float radius;
    float x; float y; float z;

    unsigned int VAO, VBO, EBO;
    unsigned int index_count;

    void computeVerticesAndIndices();
    void setup(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

public:
    Object(const float mass, const float radius, float pos[3]): mass(mass), radius(radius), x(pos[0]), y(pos[1]), z(pos[2]) {
        computeVerticesAndIndices();
    }
    ~Object();
    void draw();
    void toShader(const Shader& shader);
};


#endif //GROOVYGRAVITY_OBJECT_HPP
