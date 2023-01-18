#version 330 core

layout (location = 0) in vec2 vertices;

uniform mat4 projection;
uniform mat4 model;
uniform vec3 color;

smooth out vec4 out_color;

void main() {
	gl_Position = projection * model * vec4(vertices.xy, 0.0f, 1.0f);
	out_color = vec4(color, 1.0f);
}