#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 objectColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

uniform vec3 objectPositions[2];
uniform int objectIndex;

out vec3 vColor;

void main() {
    vec3 currentObjectPos = objectPositions[objectIndex];
    vec3 finalPos = aPos + currentObjectPos;
    gl_Position = uProj * uView * uModel * vec4(finalPos, 1.0);
    vColor = objectColor;
}
