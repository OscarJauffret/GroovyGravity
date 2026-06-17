//
// Created by Oscar Jauffret on 17/06/2026.
//

#ifndef GROOVYGRAVITY_OBJECT_HPP
#define GROOVYGRAVITY_OBJECT_HPP
#include <graphics/shader.hpp>
#include "drawable.hpp"

struct Object: public Drawable {
private:
    float mass;
    float radius;
    float x; float y; float z;

    void computeVerticesAndIndices();

public:
    Object(const float mass, const float radius, float pos[3]): mass(mass), radius(radius), x(pos[0]), y(pos[1]), z(pos[2]) {
        computeVerticesAndIndices();
    }
    void toShader(const Shader& shader);
};


#endif //GROOVYGRAVITY_OBJECT_HPP
