//
// Created by Oscar Jauffret on 17/06/2026.
//

#ifndef GROOVYGRAVITY_OBJECT_HPP
#define GROOVYGRAVITY_OBJECT_HPP
#include <graphics/shader.hpp>
#include "drawable.hpp"

struct CelestialBody: public Drawable {
private:
    const double mass;     // Mass of the celestial body in kg
    const double radius;   // Radius of the celestial body in meters
    const double renderRadius;  // Radius of the celestial body for rendering

    double x; double y; double z;  // Current position of the celestial body (in meters relative to the origin)
    double vx; double vy; double vz;   // Current velocity of the celestial body in m/s

    /**
     * Computes the vector of vertices and associated vector of indices required to create a sphere with the radius the
     * celestial body is associated with.
     *
     * This function then calls the {@link setup} function of {@link Drawable} to initialize the vertexArrays
     * @param color Color for the vertices
     */
    void computeVerticesAndIndices(glm::vec3 color);

public:
    /**
     * Initializes a celestial body
     * @param mass Mass of the celestial body in kg
     * @param radius Radius of the celestial body in meters (resized using config::render::scale)
     * @param pos Initial position of the celestial body (array containing 3 elements {x, y, z})
     * @param color Color of the celestial body
     * @param renderRadius Radius to render for the celestial body (in "opengl" units)
     */
    CelestialBody(const double mass, const double radius, double pos[3], glm::vec3 color, const double renderRadius):
    mass(mass), radius(radius), x(pos[0]), y(pos[1]), z(pos[2]), renderRadius(renderRadius) {
        computeVerticesAndIndices(color);
    }

    /**
     * Initializes a celestial body using the information from the config
     * @param celestialBody The celestial body that holds the constants used to parametrize the object.
     * @param renderRadius Radius to render for the celestial body (in "opengl" units)
     */
    CelestialBody(config::CelestialBody celestialBody, const double renderRadius) : mass(celestialBody.mass), radius(celestialBody.radius),
    x(celestialBody.pos[0]), y(celestialBody.pos[1]), z(celestialBody.pos[2]), renderRadius(renderRadius) {
        computeVerticesAndIndices(celestialBody.color);
    }

    /**
     * Draws the celestial body on the screen
     */
    void draw() override;

    // Getters and setters
    [[nodiscard]] double getMass() const;
    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;
    [[nodiscard]] double getZ() const;
    [[nodiscard]] double getVx() const;
    [[nodiscard]] double getVy() const;
    [[nodiscard]] double getVz() const;

    void setX(double tx);
    void setY(double ty);
    void setZ(double tz);
    void setVx(double tvx);
    void setVy(double tvy);
    void setVz(double tvz);

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
    friend ostream& operator<<(ostream& os, CelestialBody const& b);
};


#endif //GROOVYGRAVITY_OBJECT_HPP
