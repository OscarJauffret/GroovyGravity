//
// Created by Oscar Jauffret on 29/06/2026.
//

#ifndef GROOVYGRAVITY_PRESETS_HPP
#define GROOVYGRAVITY_PRESETS_HPP
#include "body.hpp"

namespace presets {
    static Body Sun(double renderRadius = 20.0) {
        return Body(
            BodyType::Star, 1.989e+30, 695700000.0,
            {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
            {252, 229, 112}, renderRadius
        );
    }

    static Body Earth(double renderRadius = 5.0) {
        return Body(
            BodyType::Planet, 5.9722e+24, 6371000.0,
            {152.1e9, 0.0, 0.0}, {0.0, 29290.0, 0.0},
            {192, 200, 255}, renderRadius
        );
    }
}
#endif //GROOVYGRAVITY_PRESETS_HPP
