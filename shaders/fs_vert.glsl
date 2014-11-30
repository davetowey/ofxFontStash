#version 410

in vec4  position;
in vec2  texcoord;
in vec4  color;

uniform mat4 mvp;

out vec4 colorVarying;
out vec2 texCoordVarying;
out vec4 normalVarying;

void main()
{
    colorVarying = color;
    texCoordVarying = texcoord;
    gl_Position = mvp * position;
}