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
inline void orbit(Object& o1, Object& o2, double hsq) {
    double dx = o2.getX() - o1.getX();
    double dy = o2.getY() - o1.getY();
    double dz = o2.getZ() - o1.getZ();

    cout << "dx: " << dx << ", dy: " << dy << ",dz: " << dz << endl;

    double rsq = dx * dx + dy * dy + dz * dz;
    double r = sqrt(rsq);

    double mass1 = o1.getMass();
    double mass2 = o2.getMass();

    double f = (config::physics::G * mass1 * mass2 / rsq) + (3 * config::physics::G * mass1 * mass2 * hsq) / (config::physics::c * config::physics::c * rsq * rsq);

    cout << "f: " << f << endl;

    double ax1 = f / mass1 * dx / r;
    double ay1 = f / mass1 * dy / r;
    double az1 = f / mass1 * dz / r;

    double ax2 = -f / mass2 * dx / r;
    double ay2 = -f / mass2 * dy / r;
    double az2 = -f / mass2 * dz / r;

    o1.setVx(o1.getVx() + ax1 * config::physics::dt);
    o1.setVy(o1.getVy() + ay1 * config::physics::dt);
    o1.setVz(o1.getVz() + az1 * config::physics::dt);

    o2.setVx(o2.getVx() + ax2 * config::physics::dt);
    o2.setVy(o2.getVy() + ay2 * config::physics::dt);
    o2.setVz(o2.getVz() + az2 * config::physics::dt);
}

inline double hsq(Object& o1, Object& o2) {
    double dx = o2.getX() - o1.getX();
    double dy = o2.getY() - o1.getY();
    double dz = o2.getZ() - o1.getZ();

    double dvx = o2.getVx() - o1.getVx();
    double dvy = o2.getVy() - o1.getVy();
    double dvz = o2.getVz() - o1.getVz();

    double hx = (dy * dvz) - (dz * dvy);
    double hy = (dz * dvx) - (dx * dvz);
    double hz = (dx * dvy) - (dy * dvx);

    return hx * hx + hy * hy + hz * hz;
}

#endif //GROOVYGRAVITY_OBJECTUTILS_HPP
