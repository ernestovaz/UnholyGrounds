#version 330 core

layout (location = 0) in vec4 model_coefficients;

out vec4 interpolated_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform bool render_as_black;

void main()
{

    gl_Position = projection * view * model * model_coefficients;


    if ( render_as_black )
    {
        interpolated_color = vec4(0.0f,0.0f,0.0f,1.0f);
    }
    else
    {
        interpolated_color = vec4(0.0f,0.231372f,0.435294f,1.0f);
    }
}

