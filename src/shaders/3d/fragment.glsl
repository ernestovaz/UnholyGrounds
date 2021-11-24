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

layout(location = 0) out vec4 color;

void main()
{
    vec4 origin = vec4(0.0, 1.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * vec4(0.0, 1.0, 0.0, 1.0);

    vec4 p = position_world;

    vec4 n = normalize(normal);

    vec4 light = cameraPosition - vec4(0.0, 0.6, 0.0, 0.0); //flashlight is a little lower than head, gives a cool distortion
    vec4 light_dir  = normalize(cameraDirection);
    if(isRenderingHand) //the hand has hardcoded constant ilumination
    {
        light = camera_position + vec4(0.0, 0.3, 0.0, 0.0);    
        light_dir = vec4(0.3,-0.7, 0.0, 0.0);   
    }
    float light1_angle = 0.37;
    float light2_angle = 0.43; //broader flashlight, less powerful, to smooth the contrast

/*

    //test object properties
    vec3 Kd = vec3(texture(modelTexture, textureCoord)) - 0.3f; //diffuse
    vec3 Ks = vec3(0.1, 0.1, 0.1);            //specular
    vec3 Ka = vec3(0.2, 0.2, 0.2);           //ambient
    float q = 32.0;                           //phong exponent

    vec3 I = vec3(1.0, 1.0, 1.0); 

    vec3 Ia = vec3(0.2, 0.2, 0.2); 

    vec3 lambert_diffuse_term = Kd*I*max(0, dot(n,l)); 



*/
    vec4 Kd0 = texture(modelTexture, textureCoord);
    vec4 Ks  = vec4(0.05, 0.05, 0.05, 1.0);            //specular
    vec4 Ka  = vec4(0.2, 0.2, 0.2, 1.0);           
    vec4 Ia =  vec4(0.01, 0.01, 0.01, 1.0); 
    float q = 1.0;                           //phong exponent

    if(Kd0.a < 0.01)
        discard;

    vec4 I; 

    if(dot(normalize(p-light),normalize(light_dir)) >= cos(light1_angle))
        I = vec4(0.7,0.7,0.7,0.0)*min(1, 5/length(cameraPosition-p)); //Intensity for the main flashlight
    else if(dot(normalize(p-light),normalize(light_dir)) >= cos(light2_angle))
        I = vec4(0.55,0.55,0.55,0.0)*min(1, 4/length(cameraPosition - p)) ; //Intensity for the second phase
    else
        I = vec4(0.03,0.03,0.03,0.0);
    if(isRenderingHand) //the hand has hardcoded constant ilumination
    {
        I = vec4(0.7,0.7,0.7,0.0);
    }

    if(lightingIsEnabled)
    {
        vec4 v = normalize(camera_position - p);
        vec4 r = -light + 2*n*dot(n,light); 

        vec4 lambert_diffuse_term = (Kd0 - 0.3)  * I *max(0,dot(n,light));
        vec4 ambient_term = Ka*Ia; 
        vec4 phong_specular_term  = Ks*I*pow(max(0, dot(r,v)), q); 
        color = lambert_diffuse_term + ambient_term + phong_specular_term;
    }
    else
    {
        color = Kd0 - 0.1;
    }
    
} 

