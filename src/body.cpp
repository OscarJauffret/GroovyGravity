//
// Created by Oscar Jauffret on 17/06/2026.
//

#include "body.hpp"
#include <vector>

#include "config.hpp"
#include <iostream>
#include <numbers>

using namespace std;

BodyType Body::getType() const { return type; }
double Body::getMass() const { return mass; }
double Body::getRadius() const { return radius; }
glm::dvec3 Body::getPos() const { return pos; }
glm::dvec3 Body::getVel() const { return vel; }

void Body::setPos(glm::dvec3 pos) { this->pos = pos; }
void Body::setVel(glm::dvec3 vel) { this->vel = vel; }


void Body::update() {
    pos += vel * config::physics::dt;
}
