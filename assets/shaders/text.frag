#version 330 core

in vec2 v_texture_coords;

out vec4 frag_colour;

uniform sampler2D sampler;
uniform vec3 tint;

void main() {
    frag_colour = texture(sampler, v_texture_coords) * vec4(tint, 1.0f);
}
