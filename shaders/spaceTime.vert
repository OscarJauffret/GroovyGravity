#version 410 core
layout (location = 0) in vec3 aPos;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

uniform vec3 color;

uniform float rs;
uniform vec2 objectPos;

out vec3 vColor;

void main() {
    // z(x, y) = 2 \sqrt{r_S(\sqrt{x^2 + y^2} - r_S)}
    vec3 offset = vec3(0.0);
    vec3 pos0 = aPos;

    float x = pos0.x - objectPos.x;
    float y = pos0.z - objectPos.y;
    float x2 = x * x;
    float y2 = y * y;
    float distance = sqrt(x2 + y2) - rs;
    if (distance > 0) { // means we are outside of the event horizon
        offset += vec3(0, 2 * sqrt(rs * distance), 0);
    }

    vec3 finalPos = pos0 + offset;
    gl_Position = uProj * uView * uModel * vec4(finalPos, 1.0);
    vColor = color;
}
