//
// Created by Oscar Jauffret on 29/06/2026.
//

#ifndef GROOVYGRAVITY_PRESETS_HPP
#define GROOVYGRAVITY_PRESETS_HPP
#include "physics/body.hpp"

namespace presets {
    namespace SpaceTime {
        constexpr glm::vec3 color = glm::vec3(1.0);
    }

    namespace Sun {
        constexpr glm::vec3 color = glm::vec3(252, 229, 112) / glm::vec3(255.0);
        constexpr double mass = 1.989e+30;
        constexpr double radius = 695700000.0;
        constexpr glm::dvec3 initPos = {0.0, 0.0, 0.0};
        constexpr glm::dvec3 initVel = {0.0, 0.0, 0.0};

        static Body create() {
            return Body(BodyType::Star, mass, radius, initPos, initVel, color);
        }
    };

    namespace Earth {
        constexpr glm::vec3 color = glm::vec3(192, 200, 255) / glm::vec3(255.0);
        constexpr double mass = 5.9722e+24;
        constexpr double radius = 6371000.0;
        constexpr glm::dvec3 initPos = {152.1e9, 0.0, 0.0};
        constexpr glm::dvec3 initVel = {0.0, 0.0, 29290.0};

        static Body create() {
            return Body(BodyType::Planet, mass, radius, initPos, initVel, color);
        }
    }

    namespace Moon {
        constexpr glm::vec3 color = glm::vec3(0.7f, 0.7f, 0.7f);
        constexpr double mass = 7.34767309e+22;
        constexpr double radius = 1737.4e3;
        constexpr glm::dvec3 initPos = glm::dvec3(384400e3, 0.0, 0.0) + Earth::initPos;
        constexpr glm::dvec3 initVel = glm::dvec3(0.0, 0.0, 1022.0) + Earth::initVel;

        static Body create() {
            return Body(BodyType::Satellite, mass, radius, initPos, initVel, color);
        }

    }

    namespace Mercury {
        constexpr glm::vec3 color = glm::vec3(0.7f, 0.7f, 0.7f);
        constexpr double mass = 3.3011e+23;
        constexpr double radius = 2439.7e3;
        constexpr glm::dvec3 initPos = glm::dvec3(58e9, 0.0, 0.0);
        constexpr glm::dvec3 initVel = glm::dvec3(0.0, 0.0, 47.87e3);

        static Body create() {
            return Body(BodyType::Planet, mass, radius, initPos, initVel, color);
        }

    }

    namespace Venus {
        constexpr glm::vec3 color = glm::vec3(255, 198, 73) / glm::vec3(255.0);
        constexpr double mass = 4.8675e+24;
        constexpr double radius = 6051.8e3;
        constexpr glm::dvec3 initPos = glm::dvec3(108e9, 0.0, 0.0);
        constexpr glm::dvec3 initVel = glm::dvec3(0.0, 0.0, 35.02e3);

        static Body create() {
            return Body(BodyType::Planet, mass, radius, initPos, initVel, color);
        }

    }

    namespace Mars {
        constexpr glm::vec3 color = glm::vec3(198, 123, 92) / glm::vec3(255.0);
        constexpr double mass = 6.4185e+23;;
        constexpr double radius = 3396.2e3;
        constexpr glm::dvec3 initPos = glm::dvec3(228e9, 0.0, 0.0);
        constexpr glm::dvec3 initVel = glm::dvec3(0.0, 0.0, 24e3);

        static Body create() {
            return Body(BodyType::Planet, mass, radius, initPos, initVel, color);
        }
    }

    namespace Jupiter {
        constexpr glm::vec3 color = glm::vec3(208, 164, 122) / glm::vec3(255.0);
        constexpr double mass = 1.8986e+27;
        constexpr double radius = 71488e3;
        constexpr glm::dvec3 initPos = glm::dvec3(778e9, 0.0, 0.0);
        constexpr glm::dvec3 initVel = glm::dvec3(0.0, 0.0, 13.1e3);

        static Body create() {
            return Body(BodyType::Planet, mass, radius, initPos, initVel, color);
        }
    }

    namespace Saturn {
        constexpr glm::vec3 color = glm::vec3(244, 232, 209) / glm::vec3(255);
        constexpr double mass = 5.6846e26;
        constexpr double radius = 60268e3;
        constexpr glm::dvec3 initPos = glm::dvec3(1.43e12, 0.0, 0.0);
        constexpr glm::dvec3 initVel = glm::dvec3(0.0, 0.0, 9.68e3);

        static Body create() {
            return Body(BodyType::Planet, mass, radius, initPos, initVel, color);
        }
    }

    namespace Uranus {
        constexpr glm::vec3 color = glm::vec3(172, 229, 238) / glm::vec3(255);
        constexpr double mass = 8.6810e+25;
        constexpr double radius = 25559e3;
        constexpr glm::dvec3 initPos = glm::dvec3(2.87e12, 0.0, 0.0);
        constexpr glm::dvec3 initVel = glm::dvec3(0.0, 0.0, 6.8e3);

        static Body create() {
            return Body(BodyType::Planet, mass, radius, initPos, initVel, color);
        }
    }

    namespace Neptune {
        constexpr glm::vec3 color = glm::vec3(0, 77, 153) / glm::vec3(255);
        constexpr double mass = 1.0243e+26;
        constexpr double radius = 24764e3;
        constexpr glm::dvec3 initPos = glm::dvec3(4.5e12, 0.0, 0.0);
        constexpr glm::dvec3 initVel = glm::dvec3(0.0, 0.0, 5.43e3);

        static Body create() {
            return Body(BodyType::Planet, mass, radius, initPos, initVel, color);
        }
    }

}
#endif //GROOVYGRAVITY_PRESETS_HPP
