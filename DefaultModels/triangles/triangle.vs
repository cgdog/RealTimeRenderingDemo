#version 430
layout(location = 0) in vec3 posVertex;
out vec3 pos;
void main() {
  pos = posVertex;
  gl_Position = vec4(posVertex, 1.0f);
}