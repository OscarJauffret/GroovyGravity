//
// Created by Oscar Jauffret on 17/06/2026.
//

#ifndef GROOVYGRAVITY_BODY_HPP
#define GROOVYGRAVITY_BODY_HPP
#include <graphics/shader.hpp>
#include "drawable.hpp"

enum class BodyType {
    Planet,
    Star,
    Blackhole
};

struct Body: public Drawable {
private:
    const BodyType type;        // Type of body
    const double mass;          // Mass of the body in kg
    const double radius;        // Radius of the body in meters
    const double renderRadius;  // Radius of the body for rendering TODO: move to render class

    glm::dvec3 pos;      // Current position of the body (in meters relative to the origin)
    glm::dvec3 vel;      // Current velocity og the body in m/s

    /** TODO: move this into the render class
     * Computes the vector of vertices and associated vector of indices required to create a sphere with the radius the
     * celestial body is associated with.
     *
     * This function then calls the {@link setup} function of {@link Drawable} to initialize the vertexArrays
     * @param color Color for the vertices
     */
    void computeVerticesAndIndices(glm::vec3 color);

public:
    /**
     * Initializes a body
     * @param type The type of body
     * @param mass Mass of the body in kg
     * @param radius Radius of the body in meters (resized using config::render::scale)
     * @param pos Initial position of the body ({x, y, z})
     * @param vel Initial velocity of the body ({vx, vy, vz})
     * @param color Color of the body
     * @param renderRadius Radius to render for the body (in "opengl" units)
     */
    Body(const BodyType type, const double mass, const double radius, glm::dvec3 pos, glm::dvec3 vel,
        glm::vec3 color, const double renderRadius):
    type(type), mass(mass), radius(radius), pos(pos), vel(vel), renderRadius(renderRadius) {
        computeVerticesAndIndices(color);
    }

    /**
     * Draws the celestial body on the screen TODO: move this to the render class
     */
    void draw() const override;

    // Getters and setters
    [[nodiscard]] BodyType getType() const;
    [[nodiscard]] double getMass() const;
    [[nodiscard]] glm::dvec3 getPos() const;
    [[nodiscard]] glm::dvec3 getVel() const;

    void setPos(glm::dvec3 pos);
    void setVel(glm::dvec3 vel);

    /**
     * Update the position of the celestial body according to their current speed
     */
    void update();

    /**
     * Prints the current position of the celestial body, and its speed (for debugging purposes).
     * Prints both the real and the scaled down version
     * @param os The ostream
     * @param b The celestial body to print
     * @return The ostream
     */
    friend ostream& operator<<(ostream& os, Body const& b);
};


#endif //GROOVYGRAVITY_BODY_HPP
