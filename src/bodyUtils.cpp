//
// Created by Oscar Jauffret on 25/06/2026.
//

#include "bodyUtils.hpp"

#include <glm/ext/quaternion_geometric.hpp>

void orbit(Body& b1, Body& b2, double hsq) {
    glm::dvec3 dpos = b2.getPos() - b1.getPos();

    double r =  glm::length(dpos);
    double rsq = r * r ;

    double mass1 = b1.getMass();
    double mass2 = b2.getMass();

    double f1 = (config::physics::G * mass1 * mass2 / rsq);
    double f2 = (3 * config::physics::G * mass1 * mass2 * hsq) / (config::physics::c * config::physics::c * rsq * rsq);
    double f = f1 + f2;

    glm::dvec3 a1 = f / mass1 * dpos / r;
    glm::dvec3 a2 = - f / mass2 * dpos / r;

    b1.setVel(b1.getVel() + a1 * config::physics::dt);
    b2.setVel(b2.getVel() + a2 * config::physics::dt);
}

double hsq(Body& b1, Body& b2) {
    glm::dvec3 dpos = b2.getPos() - b1.getPos();
    glm::dvec3 dvel = b2.getVel() - b1.getVel();

    glm::dvec3 h = glm::cross(dpos, dvel);
    double hNorm = glm::length(h);
    return hNorm * hNorm;
}
