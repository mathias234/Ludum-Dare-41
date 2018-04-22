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

void main()
{
    vec3 col = texture(u_ScreenTexture, texCoords).rgb;
    outColor = vec4(col, 1.0);
}