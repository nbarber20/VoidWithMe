#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D ScreenTexture;
uniform vec2 rOffset;
uniform vec2 gOffset;
uniform vec2 bOffset;
uniform float time;

float rand(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{             
    vec2 uv = TexCoords;
    
    float uvY = uv.y;
    uvY *= 100.0;
    uvY = float(int(uvY)) * (1.0 / 250);
    float noise = rand(vec2(time * 0.00001, uvY));
    uv.x += noise * 0.002;

    float colr = texture(ScreenTexture, uv +rOffset).r;
    float colg = texture(ScreenTexture, uv +gOffset).g;
    float colb = texture(ScreenTexture, uv +bOffset).b;
    FragColor = vec4(colr,colg,colb,1.0);

}