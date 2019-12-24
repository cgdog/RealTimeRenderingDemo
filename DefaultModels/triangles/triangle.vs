#version 430
layout(location = 0) in vec3 posVertex;
uniform mat4 matrix;
void main() {
  gl_Position = matrix * vec4(posVertex, 1.0f);
}
