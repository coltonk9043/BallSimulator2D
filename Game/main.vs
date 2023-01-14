#version 330 core

layout (location = 0) in vec2 vertices;
layout (location = 1) in vec2 position;
layout (location = 2) in vec4 color;

uniform mat4 projection;

smooth out vec4 out_color;

void main() {
	out_color = color;
	gl_Position = projection * vec4(vertices + position, 0.0f, 1.0f);
}