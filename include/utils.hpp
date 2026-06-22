//
// Created by Oscar Jauffret on 21/06/2026.
//

#ifndef GROOVYGRAVITY_UTILS_HPP
#define GROOVYGRAVITY_UTILS_HPP
#include <glm/vec3.hpp>
#include <iostream>
#include <vector>

using namespace std;

inline void normalizeRGB(glm::vec3& c) {
    if ( c[0] > 1.0f ||  c[1] > 1.0f ||  c[2] > 1.0f) {
         c[0] /= 255;
         c[1] /= 255;
         c[2] /= 255;
    }
}


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

#endif //GROOVYGRAVITY_UTILS_HPP
