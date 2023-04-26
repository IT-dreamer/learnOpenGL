#version 330 core

in vec4 outColor;

uniform float factor;

out vec4 fragColor;

void main(void)
{
    fragColor = factor * outColor;
}