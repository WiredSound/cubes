#version 330 core

in vec2 v_texture_coords;
in vec3 v_colour;

out vec4 frag_colour;

uniform sampler2D sampler;

void main() {
    frag_colour = texture(sampler, v_texture_coords) * vec4(v_colour, 1.0f);
}
