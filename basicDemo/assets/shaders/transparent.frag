#version 330 core


in vec2 vTextCoord;

out vec4 color;
uniform sampler2D texture_diffuse;

void main()
{             
    color = texture(texture_diffuse, vTextCoord);
}  