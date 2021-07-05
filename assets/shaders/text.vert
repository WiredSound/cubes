#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texture_coords;

uniform vec2 line_position;

out vec2 v_texture_coords;

void main() {
    gl_Position = vec4(line_position + position, 0.0f, 1.0f);
    v_texture_coords = texture_coords;
}
