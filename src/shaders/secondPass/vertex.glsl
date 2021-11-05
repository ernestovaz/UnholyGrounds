#version 330 core

layout (location = 0) in vec2 model_coefficients;
layout (location = 1) in vec2 texture_coefficients;

uniform mat4 model;

out vec2 textureCoord;

void main()
{
    gl_Position = model * vec4(model_coefficients.x, model_coefficients.y, 0.0, 1.0);
    textureCoord = texture_coefficients;
}
