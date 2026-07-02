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

        static Body create() {
            return Body(
                BodyType::Star, 1.989e+30, 695700000.0,
                {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, color
            );
        }
    };

    namespace Earth {
        constexpr glm::vec3 color = glm::vec3(192, 200, 255) / glm::vec3(255.0);

        static Body create() {
            return Body(
                BodyType::Planet, 5.9722e+24, 6371000.0,
                {152.1e9, 0.0, 0.0}, {0.0, 0.0, 29290.0}, color
            );
        }
    }

}
#endif //GROOVYGRAVITY_PRESETS_HPP
