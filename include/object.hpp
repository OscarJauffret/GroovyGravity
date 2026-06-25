//
// Created by Oscar Jauffret on 17/06/2026.
//

#ifndef GROOVYGRAVITY_OBJECT_HPP
#define GROOVYGRAVITY_OBJECT_HPP
#include <graphics/shader.hpp>
#include "drawable.hpp"

struct Object: public Drawable {
private:
    const double mass;     // Mass of the object in kg
    const double radius;   // Radius of the object in meters

    double x; double y; double z;  // Current position of the object (in meters relative to the origin)
    double vx; double vy; double vz;   // Current velocity of the object in m/s

    /**
     * Computes the vector of vertices and associated vector of indices required to create a sphere with the radius the
     * object is associated with.
     *
     * This function then calls the {@link setup} function of {@link Drawable} to initialize the vertexArrays
     * @param color Color for the vertices
     */
    void computeVerticesAndIndices(glm::vec3 color);

public:
    /**
     * Initializes an object
     * @param mass Mass of the object in kg
     * @param radius Radius of the object in meters (resized using config::render::scale)
     * @param pos Initial position of the object (array containing 3 elements {x, y, z})
     * @param color Color of the object
     */
    Object(const double mass, const double radius, float pos[3], glm::vec3 color): mass(mass), radius(radius), x(pos[0]), y(pos[1]), z(pos[2]) {
        computeVerticesAndIndices(color);
    }

    /**
     * Initializes an object using the information from the celestial body
     * @param celestialBody The celestial body to use to initialize the object
     */
    Object(config::CelestialBody celestialBody) : mass(celestialBody.mass), radius(celestialBody.radius),
    x(celestialBody.pos[0]), y(celestialBody.pos[1]), z(celestialBody.pos[2]) {
        computeVerticesAndIndices(celestialBody.color);
    }

    /**
     * Draws the object on the screen
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
     * Update the position of the object according to their current speed
     */
    void update();

    /**
     * Prints the current position of the object, and its speed (for debugging purposes).
     * Prints both the real and the scaled down version
     * @param os The ostream
     * @param o The object to print
     * @return The ostream
     */
    friend ostream& operator<<(ostream& os, Object const& o);
};


#endif //GROOVYGRAVITY_OBJECT_HPP
