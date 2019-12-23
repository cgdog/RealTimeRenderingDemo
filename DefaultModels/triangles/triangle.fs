#version 430
out vec4 fragColor;
in vec3 pos;
void main() {
  fragColor = vec4(pos.x, pos.y, pos.z, 1.0f);
}