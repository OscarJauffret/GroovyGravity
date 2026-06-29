//
// Created by Oscar Jauffret on 25/06/2026.
//

#include "objectUtils.hpp"

void orbit(CelestialBody& b1, CelestialBody& b2, double hsq) {
    double dx = b2.getX() - b1.getX();
    double dy = b2.getY() - b1.getY();
    double dz = b2.getZ() - b1.getZ();

    double rsq = dx * dx + dy * dy + dz * dz;
    double r = sqrt(rsq);

    double mass1 = b1.getMass();
    double mass2 = b2.getMass();

    double f1 = (config::physics::G * mass1 * mass2 / rsq);
    double f2 = (3 * config::physics::G * mass1 * mass2 * hsq) / (config::physics::c * config::physics::c * rsq * rsq);
    double f = f1 + f2;

    double ax1 = f / mass1 * dx / r;
    double ay1 = f / mass1 * dy / r;
    double az1 = f / mass1 * dz / r;

    double ax2 = -f / mass2 * dx / r;
    double ay2 = -f / mass2 * dy / r;
    double az2 = -f / mass2 * dz / r;

    b1.setVx(b1.getVx() + ax1 * config::physics::dt);
    b1.setVy(b1.getVy() + ay1 * config::physics::dt);
    b1.setVz(b1.getVz() + az1 * config::physics::dt);

    b2.setVx(b2.getVx() + ax2 * config::physics::dt);
    b2.setVy(b2.getVy() + ay2 * config::physics::dt);
    b2.setVz(b2.getVz() + az2 * config::physics::dt);
}

double hsq(CelestialBody& b1, CelestialBody& b2) {
    double dx = b2.getX() - b1.getX();
    double dy = b2.getY() - b1.getY();
    double dz = b2.getZ() - b1.getZ();

    double dvx = b2.getVx() - b1.getVx();
    double dvy = b2.getVy() - b1.getVy();
    double dvz = b2.getVz() - b1.getVz();

    double hx = (dy * dvz) - (dz * dvy);
    double hy = (dz * dvx) - (dx * dvz);
    double hz = (dx * dvy) - (dy * dvx);

    return hx * hx + hy * hy + hz * hz;
}

glm::vec3 center(CelestialBody& b, bool scaledToRender) {
    double x = b.getX();
    double y = b.getY();
    double z = b.getZ();
    if (scaledToRender) {
        x = scaleDistanceForRender(x);
        y = scaleDistanceForRender(y);
        z = scaleDistanceForRender(z);
    }
    return glm::vec3(x, y, z);
}
