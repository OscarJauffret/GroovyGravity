//
// Created by Oscar Jauffret on 17/06/2026.
//

#ifndef GROOVYGRAVITY_BODY_HPP
#define GROOVYGRAVITY_BODY_HPP
#include <graphics/shader.hpp>

enum class BodyType {
    Planet,
    Star,
    Blackhole
};

struct Body {
private:
    const BodyType type;        // Type of body
    const double mass;          // Mass of the body in kg
    const double radius;        // Radius of the body in meters

    glm::dvec3 pos;      // Current position of the body (in meters relative to the origin)
    glm::dvec3 vel;      // Current velocity og the body in m/s

public:
    /**
     * Initializes a body
     * @param type The type of body
     * @param mass Mass of the body in kg
     * @param radius Radius of the body in meters (resized using config::render::scale)
     * @param pos Initial position of the body ({x, y, z})
     * @param vel Initial velocity of the body ({vx, vy, vz})
     */
    Body(const BodyType type, const double mass, const double radius, glm::dvec3 pos, glm::dvec3 vel):
    type(type), mass(mass), radius(radius), pos(pos), vel(vel) {}

    // Getters and setters
    [[nodiscard]] BodyType getType() const;
    [[nodiscard]] double getMass() const;
    [[nodiscard]] double getRadius() const;
    [[nodiscard]] glm::dvec3 getPos() const;
    [[nodiscard]] glm::dvec3 getVel() const;

    void setPos(glm::dvec3 pos);
    void setVel(glm::dvec3 vel);

    /**
     * Update the position of the celestial body according to their current speed
     */
    void update();
};


#endif //GROOVYGRAVITY_BODY_HPP
