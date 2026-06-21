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
$z(x, y) = 2 \sqrt{r_S(\sqrt{x^2 + y^2} - r_S)}$, where $r_S = 2GM/c^2$

### Multiple shaders
But then I'm running into another issue. Currently, I am rendering both spacetime and the objects with the same shader.
This is annoying because they require different behavior, but need information from each other.
I will try to implement multiple shader files and see how that goes. For now, it looks like I need only to have different
vertex shaders, but the fragment shaders can be the same. 

It looks like it's as simple as just using the different shader. The fact that I have this extracted really helps.

### Back to rendering spacetime
Ok, so now let's try to implement this formula. It looks like: per object, we will need to send to the spaceTimeShader (using uniforms):
- Mass
- Position

I think we will consider only objects that are at y=0 for now (I mean only objects that are sitting on the plane). Also, something
we need to be careful of is that the $z$ axis in OpenGL is not the same as the $z$ axis of the formula. We need to swap the $z$ and $y$ axes.

So, we can fit mass + position into one vec3 vector per object.
I implemented it, but it doesn't render any different. Tried with different values for the mass, used the mass of the sun
but it doesn't move. I'll test to run the loop in a test.cpp to see, maybe the values are just super small.
Aaahh, there appears to be an overflow due to the speed of light squared: 
```
GroovyGravity/src/test.cpp:12:30: warning: overflow in expression; result is -1'394'772'636 with type 'int' [-Winteger-overflow]
float c2 = 299792458 * 299792458;
```
Hmm, now it outputs a NaN, even when using doubles. Aha, the result here is negative: $r_S(\sqrt{x^2 + y^2} - r_S)$, so it can't be 
square rooted. Yeah, well  the argument can only be positive if $\sqrt{x^2 + y^2} > r_S$, and with the sun, $r_s$ is 2954.28, so that's not good...

Aahhh, this is because Flamm's paraboloid is only valid for regions outside of the event horizon. I guess either we scale down the objects, or we scale our simulation up.
But the Sun doesn't have an event horizon, its radius is directly larger than what would be the event horizon. That's weird because the radius
of the object does not appear in the formula. For now let's scale down then. Say we have a mesh for spacetime of 1000x1000,
and we want $r_S$ = 50. So, we need a mass that is $3.36 * 10^{28}$kg.

Didn't have time to finish solving this today, so i'll continue next time