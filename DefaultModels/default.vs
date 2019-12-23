#version 430
layout(location = 0) in vec3 posVertex;
//uniform mat3 model;
out vec3 pos;
void main() {
  //pos = model * posVertex;
  pos = posVertex;
  //gl_Position = vec4(pos, 1.0f);
  gl_Position = vec4(posVertex, 1.0f);
}
