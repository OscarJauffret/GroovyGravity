//
// Created by Oscar Jauffret on 17/06/2026.
//

#ifndef GROOVYGRAVITY_SPACETIME_HPP
#define GROOVYGRAVITY_SPACETIME_HPP


#include <GL/glew.h>
#include <vector>
#include <glm/vec3.hpp>

#include "drawable.hpp"

class SpaceTime: public Drawable {
public:
    explicit SpaceTime(int resolution, float size, glm::vec3 color = {1.0, 1.0, 1.0});

    void draw() override;
};



#endif //GROOVYGRAVITY_SPACETIME_HPP
