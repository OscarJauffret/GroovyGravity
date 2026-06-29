//
// Created by Oscar Jauffret on 24/06/2026.
//

#ifndef GROOVYGRAVITY_OBJECTUTILS_HPP
#define GROOVYGRAVITY_OBJECTUTILS_HPP
#include "config.hpp"
#include "celestialBody.hpp"

/**
 * This function makes b1 and b2 orbit around each other. It updates the velocities of the celestial bodies
 * @param b1 First body
 * @param b2 Second body
 * @param hsq the square of the angular momentum. Since there is angular momentum conservation, we can compute this once and
 * reuse it
 */
void orbit(CelestialBody& b1, CelestialBody& b2, double hsq);

/**
 * Compute the square of the angular momentum. This property is conserved, so it suffices to compute it once per body pair
 * @param b1 First body
 * @param b2 Second body
 * @return The square of the angular momentum
 */
double hsq(CelestialBody& b1, CelestialBody& b2);

/**
 * Helper to get the center of a body as a glm vector
 * @param b the celestial body
 * @param scaledToRender a boolean indicating wheter the result should be returned in "render coordinates" or in "real coordinates"
 * @return the center of the body as a glm vector
 */
glm::vec3 center(CelestialBody& b, bool scaledToRender = true);

#endif //GROOVYGRAVITY_OBJECTUTILS_HPP
