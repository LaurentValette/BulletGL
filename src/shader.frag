#version 330
in vec3 light_dir, nor;
out vec4 color;
void main() {
  float d = max(dot(normalize(nor), normalize(light_dir)), 0.f);
  color = vec4(d, d, d, 1.0);
}
