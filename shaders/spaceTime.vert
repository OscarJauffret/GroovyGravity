#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 spaceTimeColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

uniform vec3 objects[1];    // x: mass, y: x, z: z

out vec3 vColor;
out vec3 vNormal;
out vec3 vPos;

void main() {;
    // z(x, y) = 2 \sqrt{r_S(\sqrt{x^2 + y^2} - r_S)}
    vec3 offset = vec3(0.0);
    vec3 pos0 = aPos;

    for (int i = 0; i < 1; i++) {
        // r_S = 2GM/c^2
        float G = 6.6743 * pow(10, -11);
        // We would like to use floats for the whole computation, because they are faster
        // But, the speed of light in m/s overflows the float. Instead, we express it in millions of m/s
        // This means that we should multiply the numerator by 10^-12. But we can't just multiply by 10^-12, because the
        // compiler would do it if he could. The problem is that the mass is not known at compile time. The solution is
        // to express the mass of the objects in millions of kilograms. Then, just a 10^-6 factor is left, and we can put this one
        // in the formula for rs
        double c2 = 299792458.0 * 299792458; // In millions of m/s
        double rs =  2 * G * objects[i].x / c2;
        double x = pos0.x - objects[i].y;
        double y = pos0.z - objects[i].z;
        double x2 = x * x;
        double y2 = y * y;
        double distance = sqrt(x2 + y2) - rs;
        if (distance > 0) { // means we are outside of the event horizon
            offset += vec3(0, 2 * sqrt(rs * distance), 0);
        }
    }
    vec3 finalPos = pos0 + offset;
    gl_Position = uProj * uView * uModel * vec4(finalPos, 1.0);
    vColor = spaceTimeColor;
    vNormal = vec3(0.0, 1.0, 0.0);
    vPos = vec3(gl_Position.x, gl_Position.y, gl_Position.z);
}
