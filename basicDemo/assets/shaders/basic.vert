#version 330 core
// Atributte 0 of the vertex
layout (location = 0) in vec3 vertexPosition;

//layout (location = 1) in vec2 texture coordenate;
layout (location = 1) in vec2 textCoord;

//layout (location = 2) in vec3 normals;
layout (location = 2) in vec3 normals;

layout (location = 3) in vec3 tangent;

layout (location = 4) in vec3 bitangent;

// Vertex data out data
out vec2 vTextCoord;
out vec3 vNormals;
out vec3 FragPos;
out mat3 TBN;
out vec3 TBNViewPos;
out vec3 TBNFragPos;
//out vec3 viewPos;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform vec3 viewPos;

void main()
{
    vTextCoord = textCoord;   
	FragPos = vec3(model * vec4(vertexPosition, 1.0f));
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0f);
	vNormals = normalize(normals);

	vec3 tang = normalize(tangent);
	mat3 modelMatrix = mat3(model);
	vec3 T = normalize(vec3(modelMatrix * tang));
	vec3 N = normalize(vec3(modelMatrix * vNormals));
	T = normalize(T-N * dot(N,T));
	//vec3 B = normalize(vec3(model * vec4(bitangent, 0.0)));
	vec3 B = normalize(cross(T,N));

	//vec3 B = normalize(vec3(normalMatrix * normalize(bitangent)));
	TBN = transpose(mat3(T, B, N));
	TBNViewPos = TBN * viewPos;
	TBNFragPos = TBN * vec3(model * vec4(vertexPosition, 1.0f));

	//TBN = transpose(mat3(T, B, N));
	//vNormals = mat3(transpose(inverse(model))) * normals;  
	//viewPos = vec3(projection*view);
}