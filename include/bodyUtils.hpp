//
// Created by Oscar Jauffret on 24/06/2026.
//

#ifndef GROOVYGRAVITY_BODYUTILS_HPP
#define GROOVYGRAVITY_BODYUTILS_HPP
#include "config.hpp"
#include "body.hpp"

/**
 * This function makes b1 and b2 orbit around each other. It updates the velocities of the bodies
 * @param b1 First body
 * @param b2 Second body
 * @param hsq the square of the angular momentum. Since there is angular momentum conservation, we can compute this once and
 * reuse it
 */
void orbit(Body& b1, Body& b2, double hsq);

/**
 * Compute the square of the angular momentum. This property is conserved, so it suffices to compute it once per body pair
 * @param b1 First body
 * @param b2 Second body
 * @return The square of the angular momentum
 */
double hsq(Body& b1, Body& b2);

#endif //GROOVYGRAVITY_BODYUTILS_HPP
