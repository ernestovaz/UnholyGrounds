#version 330 core

in vec4 interpolatedColor;

out vec4 color;

void main()
{
    color = interpolatedColor;
} 

