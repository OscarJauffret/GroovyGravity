//
// Created by Oscar Jauffret on 29/06/2026.
//

#ifndef GROOVYGRAVITY_BODYRENDERER_HPP
#define GROOVYGRAVITY_BODYRENDERER_HPP
#include "body.hpp"
#include "drawable.hpp"

class BodyRenderer: public Drawable {
public:
    /**
     * Initialize a renderer for a given body. Computes the vector of vertices and associated vector of indices
     * required to create a sphere a radius of 1
     *
     * This function then calls the {@link setup} function of {@link Drawable} to initialize the vertexArrays
     */
    BodyRenderer();

    /**
     * Draws the body on the screen
     */
    void draw() const override;

    /**
     * Prints the current position of the body, and its speed (for debugging purposes).
     * Prints both the real and the scaled down version
     * @param os The ostream
     * @param b The celestial body to print
     * @return The ostream
     */
    friend ostream& operator<<(ostream& os, Body const& b);
};


#endif //GROOVYGRAVITY_BODYRENDERER_HPP
