#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 objectColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

out vec3 vColor;

void main() {
    //vec3 objectPos = vec3(object[0], object[1], object[2]);
    gl_Position = uProj * uView * uModel * vec4(aPos[0], aPos[1], aPos[2], 1.0);
    vColor = objectColor;
}
