#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 objectColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

out vec3 vColor;
out vec3 vNormal;
out vec3 vPos;

void main() {
    gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
    vColor = objectColor;

    vPos = vec3(uModel * vec4(aPos, 1.0));
    vNormal = normalize(mat3(uModel) * aPos);
}
