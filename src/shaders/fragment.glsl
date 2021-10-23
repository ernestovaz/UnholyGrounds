#version 330 core

in vec4 position_world;
in vec4 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform int object_id;

out vec3 color;

void main()
{
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    vec4 p = position_world;

    vec4 n = normalize(normal);

    vec4 l = normalize(vec4(1.0,1.0,0.5,0.0));

    vec4 v = normalize(camera_position - p);

    vec4 r = -l + 2*n*dot(n,l); 

    //test object properties
    vec3 Kd = vec3(0.08, 0.23137, 0.4352941); //diffuse
    vec3 Ks = vec3(0.8, 0.8, 0.8);            //specular
    vec3 Ka = vec3(0.04, 0.2, 0.4);           //ambient
    float q = 32.0;                           //phong exponent

    vec3 I = vec3(1.0, 1.0, 1.0); 

    vec3 Ia = vec3(0.2, 0.2, 0.2); 

    vec3 lambert_diffuse_term = Kd*I*max(0, dot(n,l)); 

    vec3 ambient_term = Ka*Ia; 

    vec3 phong_specular_term  = Ks*I*pow(max(0, dot(r,v)), q); 

    color = lambert_diffuse_term + ambient_term + phong_specular_term;

    color = pow(color, vec3(1.0,1.0,1.0)/2.2);
} 

