#version 430
layout (location =0) in vec3 position;
layout (location =1) in vec3 normal;
out vec3 vPos;
out vec3 vNormal;

uniform mat4 uModel;
uniform mat4 viewProj;

void main() {
    vec4 worldPosition = uModel * vec4(position, 1.0) ;
    vPos = worldPosition. xyz;
    vNormal = (uModel * vec4(normal, 0.0)).xyz;
    gl_Position = viewProj * worldPosition ;
}
