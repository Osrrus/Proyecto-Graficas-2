#version 330 core
// Atributte 0 of the vertex
layout (location = 0) in vec3 vertexPosition;

// Vertex data out data
out vec3 vTextCoord;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    vTextCoord = vertexPosition;   
    gl_Position = projection * view * vec4(vertexPosition, 1.0f);
}