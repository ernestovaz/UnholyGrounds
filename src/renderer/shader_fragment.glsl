#version 330 core

in vec4 interpolated_color;

out vec4 color;

void main()
{
    color = interpolated_color;
} 

