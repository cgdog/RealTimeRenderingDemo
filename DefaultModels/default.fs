#version 430
out vec4 fragColor;
in vec3 pos;
void main() {
  vec3 color = (pos + 1.0f) * 0.5f;
  fragColor = vec4(color, 1.0f);
}