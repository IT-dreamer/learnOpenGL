#version 330 core

in vec4 vary_color;

out vec4 FragColor;

void main()
{
    FragColor = vary_color;
}