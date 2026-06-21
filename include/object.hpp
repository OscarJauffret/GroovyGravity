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

    void computeVerticesAndIndices(glm::vec3 color);

public:
    Object(const float mass, const float radius, float pos[3], glm::vec3 color): mass(mass), radius(radius), x(pos[0]), y(pos[1]), z(pos[2]) {
        computeVerticesAndIndices(color);
    }
    void draw() override;

    [[nodiscard]] float getMass() const;
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getZ() const;

};


#endif //GROOVYGRAVITY_OBJECT_HPP
