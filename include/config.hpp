//
// Created by Oscar Jauffret on 17/06/2026.
//

#ifndef GROOVYGRAVITY_CONFIG_HPP
#define GROOVYGRAVITY_CONFIG_HPP

namespace config {

    namespace render {
        constexpr int angular_resolution = 20;      // How many vertices are used to make a circle (this is used to make spheres)
        constexpr double distanceScale = 1.0f / 1000000000;    // How much to scale the distances by for rendering
        constexpr double radiiScale = 1.0f / 25000000;        // How much to scale the radii by for rendering

    }

    namespace window {
        constexpr int width = 800;  // Width of the window
        constexpr int height = 600; // Height of the window
    }

    namespace physics {
        constexpr double dt = 2500;       // timestep (used to compute next orbit step)
        constexpr double G = 6.6743e-11;    // Universal gravitational constant
        constexpr double c = 299792458.0f;  // Speed of light in a vacuum
    }

    struct CelestialBody {
        const double mass;       // Mass in kg
        const double radius;     // Radius in m
        float pos[3];           // Initial position in m with respect to the origin
        const glm::vec3 color;  // Color
    };

    struct CelestialBodies {
        inline static const CelestialBody Sun {1.989e30, 696000000.0f,{0.0f, 0.0f, 0.0f}, {252, 229, 112}};
        inline static const CelestialBody Earth {5.9722e+24, 63710000.0f, {152.1e9f, 0.0f, 0.0f}, {192, 200, 255}};
    };
}

#endif //GROOVYGRAVITY_CONFIG_HPP
