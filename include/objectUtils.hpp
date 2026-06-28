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

/**
 * Compute the square of the angular momentum. This propertys is conserved, so it suffices to compute it once per object pair
 * @param o1 First object
 * @param o2 Second object
 * @return The square of the angular momentum
 */
double hsq(Object& o1, Object& o2);

/**
 * Helper to get the center of an object as a glm vector
 * @param o the object
 * @param scaledToRender a boolean indicating wheter the result should be returned in "render coordinates" or in "real coordinates"
 * @return the center of the object as a glm vector
 */
glm::vec3 center(Object& o, bool scaledToRender = true);

#endif //GROOVYGRAVITY_OBJECTUTILS_HPP
