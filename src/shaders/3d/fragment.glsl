#version 330 core

in vec4 position_world;
in vec4 normal;
in vec2 textureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform sampler2D modelTexture;

uniform bool lightingIsEnabled;
uniform bool isRenderingHand;

uniform vec4 cameraPosition;
uniform vec4 cameraDirection;

layout(location = 0) out vec3 color;

void main()
{
    vec4 origin = vec4(0.0, 1.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * vec4(0.0, 1.0, 0.0, 1.0);

    vec4 p = position_world;

    vec4 n = normalize(normal);

    vec4 l;
    vec4 l_dir  = normalize(cameraDirection);
    if(isRenderingHand)
    {
        l = vec4(0.0, 4.0, -1.0, 0.0); 
        l_dir  = vec4(0.0, -1.0, 0.0, 0.0); 
    }
    else
    { 
        l = cameraPosition;
        l_dir  = normalize(cameraDirection);
    }
    float l_angle = 0.5;//0.523599;

/*
    vec4 v = normalize(camera_position - p);

    vec4 r = -l + 2*n*dot(n,l); 

    //test object properties
    vec3 Kd = vec3(texture(modelTexture, textureCoord)) - 0.3f; //diffuse
    vec3 Ks = vec3(0.1, 0.1, 0.1);            //specular
    vec3 Ka = vec3(0.2, 0.2, 0.2);           //ambient
    float q = 32.0;                           //phong exponent

    vec3 I = vec3(1.0, 1.0, 1.0); 

    vec3 Ia = vec3(0.2, 0.2, 0.2); 

    vec3 lambert_diffuse_term = Kd*I*max(0, dot(n,l)); 

    vec3 ambient_term = Ka*Ia; 

    vec3 phong_specular_term  = Ks*I*pow(max(0, dot(r,v)), q); 

    color = lambert_diffuse_term + ambient_term + phong_specular_term;
*/
    vec3 Kd0 = texture(modelTexture, textureCoord).rgb;

    vec3 I; 

    if(dot(normalize(p-l),normalize(l_dir)) < cos(l_angle))
        I = vec3(0.04,0.04,0.04);
    else
        I = vec3(0.3,0.3,0.3); 

    if(lightingIsEnabled)
    {
        // Equação de Iluminação
        float lambert = max(0,dot(n,l));
        color = (Kd0 - 0.3)  * (I*lambert);
        //color = pow(color, vec3(1.0,1.0,1.0)/2.2);
    }
    else
    {
        color = Kd0 - 0.1;
    }
    
    // Cor final com correção gamma, considerando monitor sRGB.
    // Veja https://en.wikipedia.org/w/index.php?title=Gamma_correction&oldid=751281772#Windows.2C_Mac.2C_sRGB_and_TV.2Fvideo_standard_gammas
} 

