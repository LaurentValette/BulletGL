#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
out vec3 light_dir, nor;
uniform mat4 model, view, projection;
uniform vec3 light_pos;

void main() {
  vec4 vertex_mv = view * model * vec4(position, 1.0);
  gl_Position = projection * vertex_mv;
  nor = (transpose(inverse(view * model)) * vec4(normal, 0.0)).xyz;
  light_dir = (view * vec4(light_pos, 1.0)).xyz - vertex_mv.xyz;
}
