#shader vertex
#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec4 color;

uniform mat4 u_ProjectionMatrix;

out vec2 texCoord0;
out vec4 color0;

void main()
{
    texCoord0 = texCoord;
    color0 = color;
    gl_Position = u_ProjectionMatrix * vec4(position.xy,0,1);
}

#shader fragment
#version 330 core

uniform sampler2D u_Texture;
in vec2 texCoord0;
in vec4 color0;
out vec4 outColor;

void main()
{
    outColor = color0 * texture( u_Texture, texCoord0.st);
}