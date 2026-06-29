//
// Created by Oscar Jauffret on 29/06/2026.
//

#include "universe.hpp"

void Universe::addBody(Body body) {
    bodies.emplace_back(body);
    validHsqMatrix = false;
}

void Universe::computeHsqMatrix() {
    unsigned int n = bodies.size();
    hsqMatrix.resize(n, std::vector(n, 0.0));
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            hsqMatrix[i][j] = hsq(bodies[i], bodies[j]);
        }
    }
    validHsqMatrix = true;
}

void Universe::update() {
    unsigned int n = bodies.size();
    if (n == 0) return;
    if (!validHsqMatrix) computeHsqMatrix();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            orbit(bodies[i], bodies[j], hsqMatrix[i][j]);
        }
    }
    for (auto& b : bodies) {
        b.update();
    }
}

const vector<Body>& Universe::getBodies() const {
    return bodies;
}
