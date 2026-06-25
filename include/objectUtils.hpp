//
// Created by Oscar Jauffret on 24/06/2026.
//

#ifndef GROOVYGRAVITY_OBJECTUTILS_HPP
#define GROOVYGRAVITY_OBJECTUTILS_HPP
#include "config.hpp"
#include "object.hpp"

/**
 * This function makes o1 and o2 orbit around each other. It updates the velocities of the objects
 * @param o1 First object
 * @param o2 Second object
 * @param hsq the square of the angular momentum. Since there is angular momentum conservation, we can compute this once and
 * reuse it
 */
void orbit(Object& o1, Object& o2, double hsq);

double hsq(Object& o1, Object& o2);

#endif //GROOVYGRAVITY_OBJECTUTILS_HPP
