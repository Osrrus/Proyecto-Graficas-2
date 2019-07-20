#version 330 core
// Vertex color (interpolated/fragment)
in vec3 vTextCoord;
in vec3 FragPos;
// Fragment Color
out vec4 color;

uniform samplerCube skybox_texture;

void main()
{
    color = texture(skybox_texture, vTextCoord);
}