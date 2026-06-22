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
of the object does not appear in the formula. For now let's scale down then. Say we have a mesh for spacetime of 300x300,
and we want $r_S$ = 5. So, we need a mass that is 

$mass = c^2 r_S/2G = 3.36648 * 10^{27}$

Didn't have time to finish solving this today, so i'll continue next time

## 22/06
It is possible that the formula I have is not suited for objects that do not have an even horizon, i don't know.

Hmm, when i send the object to the shader, the object itself is no longer drawn. If we pass by reference it works.

I don't understand, because it seems like only the point at {0, 0} is being passed through the spaceTimeShader.
![image](img/2026-06-22_Only_00.png)
This is with this code in spaceTime.vert:
```c++
for (int i = 0; i < 1; i++) {
    // r_S = 2GM/c^2
    float G = 6.6743 * pow(10, -11);
    double c2 = 299792458 * 299792458;
    double rs =  2 * G * objects[i].x / c2;
    float x2 = aPos[0] * aPos[0];
    float y2 = aPos[2] * aPos[2];
    if ((sqrt(x2 + y2) - rs) > 0) { // means we are outside of the event horizon
        offset -= vec3(0, 2 * sqrt(rs * (sqrt(x2 + y2) - rs)), 0);
    } else { // Otherwise, we will offset a certain value i suppose
        offset -= vec3(0, 5, 0);
    }
}
```
I thought it could have been because we need to reference aPos.x, and not aPos[0], but apparently not..

When i remove the if check, and always offset by 5, it works, and I also notice that the FPS is much better (this part could be
because there is no if anymore). Maybe it is because of the presence of the if statement (gpu doesn't like it? I know they don't like
branching but come on, just a little bit of branching). But when i have an if statement outside
of a for loop, it seemed to work. I'll try removing the for loop for now.

Doesn't solve it, but at least that means that we'll be able to use our for loop later.

I tried coloring the vertices with respect to their distance to the origin. My goal was to color vertices that 
are close to {0, 0} in black, and far from {0, 0} go to red. It seems like it's working, the pixel in the very center is black
```c++
double distanceToOrigin = sqrt(x2 + y2);
vec3 c = vec3(1.0, 0, 0) * vec3(1 - 1/(distanceToOrigin + 1));
```
![image](img/2026-06-22_red.png)
![image](img/2026-06-22_center_black.png)
Hm but it does work apparently, because when I change the color to green when it enters the if, it works
```c++
if (distance > 0) { // means we are outside of the event horizon
    offset -= vec3(0, 2 * sqrt(rs * distance), 0);
    c = vec3(0.0, 1.0, 0.0);
} else { // Otherwise, we will offset a certain value i suppose
    offset -= vec3(0, 5.0, 0);
    c = vec3(1.0, 0.0, 0.0);
}
```
But everything is still so flat, and I also don't understand why it's just the pixel at the very center that is red
![image](img/2026-06-22_green.png)

Could it be that the units used in the formula (meters), and the units defining my sphere (I thought they were meters) are not the same?
Let's check what values the vertices of the spaceTime mesh are

[-5, 0, -5, 1, 1, 1, -5, 0, -4, 1, 1, 1, -5, 0, -3, 1, 1, 1, -5, 0, -2, 1, 1, 1, -5, 0, -1, 1, 1, 1 ...]

Yeah well that seems about right, the values are not close to zero or anything ({1, 1, 1} is just the color).
Ì'm lost.

It also seems like the units for the spacetime mesh are the same as the ones for the sphere, because when I generate a 
mesh with size 10, it perfectly fits the sphere.

Hmmmmmm, it seems like rs is always smaller than 0: 
```c++
double rs =  2 * G * objects[0].x / c2;
if (rs < 1e-3) {
    c = vec3(0.0, 1.0, 1.0);
}
```
This does indeed color the mesh cyan. Interesting because it should be close to 5 with the values we are using.

I FOUND IT, when i wrote the lambda function to send the objects to the shader, i forgot an "s" at "objects"...... oops 😶‍🌫️
```c++
auto sendObjectToSpaceTimeShader = [&spaceTimeShader](Object& object, int id) {
    spaceTimeShader.setVec3("objects[" + std::to_string(id) + "]", glm::vec3(object.getMass(), object.getX(), object.getZ()));
};
```

![image](img/2026-06-22_curved_spacetime.png)

Alright, now I'd like to be able to have multiple objects that each curve spacetime. For this, I need to change the formula a
little bit, because currently, it only curves spacetime at the origin, regardless of the position of the object: example with a
second object that has the same mass as the first one, but twice the radius:

![image](img/2026-06-22_two_masses_formula_not_adapted.png)

Clearly, spacetime is bent twice in the same location. Here is my first attempt: we do a change of coordinates:
```c++
uniform vec3 objects[2];    // x: mass, y: x, z: z
[...]
float x = pos0.x - objects[i].y;
float y = pos0.z - objects[i].z;
float x2 = x * x;
float y2 = y * y;
```

It looks alright, but there seems to be something missing, because it stops before it can reach the objects
![image](img/2026-06-22_two_masses_not_yet.png)

I'm also not too sure how to choose the masses and the radii. In real life, the sun's radius is much larger than the associated $r_s$
For now, I think i'll keep objects that have a radius that is exactly $r_s$. This means for the second mass, we need to reduce its mass:

$mass = c^2 r_S/2G = 6.73295 * 10^{27}$

Twice as massive, who would've thought. I think I'd rather have an object that's half the radius and half the mass in the end.

![image](img/2026-06-22_two_masses_not_yet_smaller.png)
Now it's a bit clearer. It looks like there's just an offset. Maybe it's because there is a "static" component to the curvature
that is then being added twice (for each object). 

Maybe Flamm's paraboloid is not additive. annoying

Also, [this article](https://physics.stackexchange.com/questions/561289/shape-of-curved-spacetime#:~:text=However%2C%20it%20should,as%20in%20space.) says that
Flamm's paraboloid only describes space, and not spacetime. That is fine for our visualization I think

Maybe Flamm's paraboloid isn't what we need in the end? Also, I have no idea how it'll help us to then have objects follow the gravity field.