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

uniform sampler2D u_ScreenTexture;
uniform float u_Exposure;
uniform float u_Gamma;

void main()
{
    vec3 hdrColor = texture(u_ScreenTexture, texCoords).rgb;

    // Exposure tone mapping
    vec3 mapped = vec3(1.0) - exp(-hdrColor * u_Exposure);
    // Gamma correction
    mapped = pow(mapped, vec3(1.0 / u_Gamma));

    outColor = vec4(mapped, 1.0);
}