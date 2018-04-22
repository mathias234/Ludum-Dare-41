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

uniform sampler2D u_Image;

uniform bool u_Horizontal;
uniform float u_Weights[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

void main()
{
     float weight = u_Weights[0];


     vec2 tex_offset = 1.0 / textureSize(u_Image, 0); // gets size of single texel
     vec3 result = texture(u_Image, texCoords).rgb * weight;
     if(u_Horizontal)
     {
         for(int i = 1; i < 5; ++i)
         {
            result += texture(u_Image, texCoords + vec2(tex_offset.x * i, 0.0)).rgb * u_Weights[i];
            result += texture(u_Image, texCoords - vec2(tex_offset.x * i, 0.0)).rgb * u_Weights[i];
         }
     }
     else
     {
         for(int i = 1; i < 5; ++i)
         {
             result += texture(u_Image, texCoords + vec2(0.0, tex_offset.y * i)).rgb * u_Weights[i];
             result += texture(u_Image, texCoords - vec2(0.0, tex_offset.y * i)).rgb * u_Weights[i];
         }
     }
     outColor = vec4(result, 1.0);
}