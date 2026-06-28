#version 410 core
in vec3 vColor;
in vec3 vNormal;
in vec3 vPos;

uniform vec3 sunPosition;
uniform bool lightSource;

out vec4 FragColor;

void main() {
    vec3 objToSun = normalize(sunPosition - vPos);
    float tint = dot(normalize(vNormal), objToSun);

    float darkTint = lightSource ? 1.0 : 0.2;
    tint = max(tint, darkTint);
    FragColor = vec4(vColor * tint, 1.0);
}
