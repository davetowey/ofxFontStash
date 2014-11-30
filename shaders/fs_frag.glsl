#version 410

uniform sampler2D src_tex_unit0;
out vec4 fragColor;

in vec4 colorVarying;
in vec2 texCoordVarying;

void main(){
    
   fragColor = texture(src_tex_unit0, texCoordVarying).rrrr * colorVarying;
}