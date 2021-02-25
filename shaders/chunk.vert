#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colour;

uniform mat4 view;
uniform mat4 projection;

out vec3 v_colour;

void main() {
    gl_Position = projection * view * mat4(1.0f) * vec4(position, 1.0f);
    v_colour = colour;
}
