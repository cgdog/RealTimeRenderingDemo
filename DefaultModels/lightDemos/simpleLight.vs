#version 430
layout (location =0) in vec4 position;
layout (location =1) in vec4 normal;
out vec3 vPos;
out vec3 vNormal;

uniform mat4 uModel;
uniform mat4 viewProj;

void main() {
    vec4 worldPosition = uModel * position ;
    vPos = worldPosition . xyz;
    vNormal = (uModel * normal).xyz;
    gl_Position = viewProj * worldPosition ;
}
