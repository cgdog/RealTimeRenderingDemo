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
    //vNormal = (transpose(inverse(uModel)) * vec4(normal, 0.0)).xyz;
    // 由于在世界空间中进行的光照计算，且模型只发生了平移，而平移对法线无影响,所以无需对法线坐标处理。
    vNormal = normal;
    gl_Position = viewProj * worldPosition ;
}
