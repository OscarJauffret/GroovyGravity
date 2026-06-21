//
// Created by Oscar Jauffret on 21/06/2026.
//

#ifndef GROOVYGRAVITY_UTILS_HPP
#define GROOVYGRAVITY_UTILS_HPP
#include <glm/vec3.hpp>

inline void normalizeRGB(glm::vec3& c) {
    if ( c[0] > 1.0f ||  c[1] > 1.0f ||  c[2] > 1.0f) {
         c[0] /= 255;
         c[1] /= 255;
         c[2] /= 255;
    }
}

#endif //GROOVYGRAVITY_UTILS_HPP
