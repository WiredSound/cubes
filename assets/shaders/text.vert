#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texture_coords;
layout (location = 2) in vec3 colour;

out vec2 v_texture_coords;
out vec3 v_colour;

void main() {
    gl_Position = vec4(position, 0.0f, 1.0f);
    v_texture_coords = texture_coords;
    v_colour = colour;
}
