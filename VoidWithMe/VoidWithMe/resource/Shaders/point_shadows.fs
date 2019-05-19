#version 330 core

#define MAX_POINT_LIGHTS 10
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;



uniform int Num_Lights;
uniform sampler2D diffuseTexture;
uniform samplerCube[MAX_POINT_LIGHTS] depthMap;

uniform vec3[MAX_POINT_LIGHTS] lightPos;

uniform vec3 viewPos;

uniform float far_plane;
uniform bool shadows;


// array of offset direction for sampling
vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float ShadowCalculation(vec3 fragPos , vec3 pointLightPos, int index)
{
    vec3 fragToLight = fragPos - pointLightPos;
    float currentDepth = length(fragToLight);
    float shadow = 0.0;
    float bias = 0.20;
    int samples = 5;
    float viewDistance = length(viewPos - fragPos);
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    for(int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(depthMap[index], fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= far_plane;   // undo mapping [0;1]
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);
        
    return shadow;
}

vec3 CalcPointLight(vec3 lightPos)
{
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightColor = vec3(0.3);

    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * vec3(0.3);
    return (diffuse);
}

void main()
{           

    
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    //ambient
    vec3 ambient = 0.3 * texture(diffuseTexture, fs_in.TexCoords).rgb;
    // diffuse


    vec3 diffuse;	
    for(int i = 0; i < Num_Lights; i++)
    	diffuse += CalcPointLight(lightPos[i]);

    float shadow;
    for(int i = 0; i < Num_Lights; i++)  
    	shadow += ShadowCalculation(fs_in.FragPos,lightPos[i],i)*.1;   





                 
    vec3 lighting = (ambient + (diffuse.x - shadow) * diffuse) * color;   
    
    FragColor = vec4(lighting, 1.0);
}
