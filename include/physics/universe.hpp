//
// Created by Oscar Jauffret on 29/06/2026.
//

#ifndef GROOVYGRAVITY_UNIVERSE_HPP
#define GROOVYGRAVITY_UNIVERSE_HPP

#include <vector>
#include "body.hpp"
#include "bodyUtils.hpp"
using std::vector;

class Universe {
private:
    vector<Body> bodies;
    vector<vector<double>> hsqMatrix;
    bool validHsqMatrix = false;

    void computeHsqMatrix();
public:
    void addBody(Body body);
    void update();
    const vector<Body>& getBodies() const;
};


#endif //GROOVYGRAVITY_UNIVERSE_HPP
