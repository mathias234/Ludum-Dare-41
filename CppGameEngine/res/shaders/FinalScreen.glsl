#shader vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 texCoords;

void main()
{
    texCoords = texCoord;
    gl_Position = vec4(position, 1.0);
}


#shader fragment
#version 330 core

out vec4 outColor;

in vec2 texCoords;

uniform sampler2D u_Scene;
uniform sampler2D u_BloomBlur;
uniform float u_Exposure;
uniform float u_Gamma;
uniform bool u_Bloom;

void main()
{

    vec3 hdrColor = texture(u_Scene, texCoords).rgb;
    vec3 bloomColor = texture(u_BloomBlur, texCoords).rgb;
    if(u_Bloom)
        hdrColor += bloomColor; // additive blending

    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * u_Exposure);
    // also gamma correct while we're at it
    result = pow(result, vec3(1.0 / u_Gamma));
    outColor = vec4(result, 1.0);
}