#version 330 core

in vec3 v_colour;

out vec4 frag_colour;

void main() {
    frag_colour = vec4(v_colour, 1.0f);
} 
