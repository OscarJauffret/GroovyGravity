#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 spaceTimeColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

uniform vec3 objects[2];    // x: mass, y: x, z: z

out vec3 vColor;

void main() {;
    // z(x, y) = 2 \sqrt{r_S(\sqrt{x^2 + y^2} - r_S)}
    vec3 offset = vec3(0.0);
    vec3 pos0 = aPos;
    vec3 c;

    for (int i = 0; i < 1; i++) {
            // r_S = 2GM/c^2
        float G = 6.6743 * pow(10, -11);
        double c2 = 299792458.0 * 299792458;
        double rs =  2 * G * objects[0].x / c2;
        float x2 = pos0.x * pos0.x;
        float y2 = pos0.z * pos0.z;
        double distance = sqrt(x2 + y2) - rs;
        if (distance > 0) { // means we are outside of the event horizon
            offset += vec3(0, 2 * sqrt(rs * distance), 0);
        }
    }
    vec3 finalPos = pos0 + offset;
    gl_Position = uProj * uView * uModel * vec4(finalPos, 1.0);
    vColor = spaceTimeColor;
}
