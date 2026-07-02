//
// Created by Oscar Jauffret on 21/06/2026.
//

#ifndef GROOVYGRAVITY_UTILS_HPP
#define GROOVYGRAVITY_UTILS_HPP
#include <glm/vec3.hpp>
#include <iostream>
#include <vector>

#include "config/config.hpp"

using namespace std;

/**
 * Helper that checks if a color is in RGB but scaled to 255, and scales it to 1 if it is the case
 * @param c the color to check and normalize
 */
inline void normalizeRGB(glm::vec3& c) {
    if ( c[0] > 1.0f ||  c[1] > 1.0f ||  c[2] > 1.0f) {
         c[0] /= 255;
         c[1] /= 255;
         c[2] /= 255;
    }
}

/**
 * Helper to print a vector
 * @tparam T The type of vector
 * @param os The ostream
 * @param v The vector to print
 * @return The ostream
 */
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << ", ";
    }
    os << "]\n";
    return os;
}

/**
 * Template function to scale down a value (used to scale down distances in the simulation)
 * @tparam T The type of the value
 * @param val The value
 * @return The scaled down value
 */
template <typename T>
T scaleDistanceForRender(T val) {
    return config::render::distanceScale * val;
}

#endif //GROOVYGRAVITY_UTILS_HPP
