//
// Created by Oscar Jauffret on 17/06/2026.
//

#ifndef GROOVYGRAVITY_CONFIG_HPP
#define GROOVYGRAVITY_CONFIG_HPP
#include <glm/vec3.hpp>

namespace config {

    namespace render {
        constexpr int angular_resolution = 50;      // How many vertices are used to make a circle (this is used to make spheres)
        constexpr double distanceScale = 1.0 / 1000000000;    // How much to scale the distances by for rendering

    }

    namespace window {
        constexpr int width = 800;  // Width of the window
        constexpr int height = 600; // Height of the window
    }

    namespace physics {
        constexpr double dt = 10000;       // timestep (used to compute next orbit step)
        constexpr double G = 6.6743e-11;    // Universal gravitational constant
        constexpr double c = 299792458.0f;  // Speed of light in a vacuum
    }
}

#endif //GROOVYGRAVITY_CONFIG_HPP
