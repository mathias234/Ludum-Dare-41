#shader vertex
#version 330 core

layout(location = 0) in vec3 position;


uniform mat4 u_LightSpaceMatrix;
uniform mat4 u_ModelMatrix;

void main()
{
    gl_Position = u_LightSpaceMatrix * u_ModelMatrix * vec4(position, 1.0);
}

#shader fragment
#version 330 core

void main()
{
    // This happens behind the scenes so we dont need to do it here.
    // gl_FragDepth = gl_FragCoord.z;
}