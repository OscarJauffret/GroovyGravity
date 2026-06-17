//
// Created by Oscar Jauffret on 17/06/2026.
//

#ifndef GROOVYGRAVITY_SPACETIME_HPP
#define GROOVYGRAVITY_SPACETIME_HPP


#include <GL/glew.h>
#include <vector>

#include "drawable.hpp"

class SpaceTime: public Drawable {
public:
    explicit SpaceTime(int resolution, float size);

    void draw() override;
};



#endif //GROOVYGRAVITY_SPACETIME_HPP
