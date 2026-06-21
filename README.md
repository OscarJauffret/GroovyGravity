# GroovyGravity

Hello, I'll document my progress here for future reference

## 17/06
Started the project, used parts of my Ocean Simulation to get a quickstart, and managed to draw a sphere
using the following sources, and some help from a friend:
- https://learnopengl.com/Getting-started/Hello-Triangle
- http://www.songho.ca/opengl/gl_sphere.html

Then, I added in a mesh that i took from OceanSim, for now I'll just draw it statically. And I extract what's common in a 
Drawable abstract class

## 21/06 
### Cleanup from last time
Today I would like to get the curvature of spacetime to work. I first started by putting the color information of the objects
in the vertices directly, rather than relying on a uniform to switch over different colors. I also fixed a bug with the sphere
generation, basically I noticed that when i placed a sphere not in the center, it had lines going to the origin. It was due to the
fact that I had gotten the boundary conditions wrong when generating the vertices.

### Rendering spacetime
Then, I started reading wikipedia ([spacetime](https://en.wikipedia.org/wiki/Spacetime#), [curved spacetime](https://en.wikipedia.org/wiki/Curved_spacetime#))
to get some information on how I could render spacetime like you see often rendered, as a sort of paraboloid.
This was wayy to complicated, but I remembered I had once seen a [youtube video](https://www.youtube.com/watch?v=_YbGWoUaZg0) of a guy that simulated gravity,
so I went and rewatched it. Turns out what I am trying to render is a Flamm paraboloid. Knowing this, I searched [wikipedia](https://en.wikipedia.org/wiki/Schwarzschild_metric#Flamm's_paraboloid)
I still couldn't, from the wikipedia article, figure out how I could turn this into code. I decided to go watch a [video](https://www.youtube.com/watch?v=qbU6WcWrHO4) to try to understand a bit more

This video seems perfect, it's telling me how to represent the paraboloid: 
$z(x, y) = 2 \sqrt{r_S(\sqrt{x^2 + y^2} - r_S)}$, where $r_S = 2GM/c^2 $

### Multiple shaders
But then I'm running into another issue. Currently, I am rendering both spacetime and the objects with the same shader.
This is annoying because they require different behavior, but need information from each other.
I will try to implement multiple shader files and see how that goes. For now, it looks like I need only to have different
vertex shaders, but the fragment shaders can be the same. 

It looks like it's as simple as just using the different shader. The fact that I have this extracted really helps