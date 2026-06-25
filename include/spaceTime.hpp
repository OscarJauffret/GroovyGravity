//
// Created by Oscar Jauffret on 17/06/2026.
//

#ifndef GROOVYGRAVITY_SPACETIME_HPP
#define GROOVYGRAVITY_SPACETIME_HPP


#include <GL/glew.h>
#include <vector>
#include <glm/vec3.hpp>

#include "drawable.hpp"

class SpaceTime: public Drawable {
public:
    /**
     * This function creates a space time mesh drawable object that shows a mesh of size x size meters. This mesh is bent
     * by the objects that are sent to the space time shader.
     *
     * @param resolution Resolution of the space time mesh (only matters for visualization)
     * @param size Size of the space time mesh in meters, resized using the config::render::scale
     * @param color The color of the mesh
     */
    explicit SpaceTime(int resolution, double size, glm::vec3 color = {1.0, 1.0, 1.0});

    /**
     * Draws the mesh on the screen
     */
    void draw() override;
};



#endif //GROOVYGRAVITY_SPACETIME_HPP
