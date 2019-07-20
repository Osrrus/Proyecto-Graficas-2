#include "CubeMap.h"

CubeMap::CubeMap(std::vector<std::string> faces)
{   
    float Vertices[] = {
        
        -50.0f,  50.0f, -50.0f,
        -50.0f, -50.0f, -50.0f,
        50.0f, -50.0f, -50.0f,
        50.0f, -50.0f, -50.0f,
        50.0f,  50.0f, -50.0f,
        -50.0f,  50.0f, -50.0f,

        -50.0f, -50.0f,  50.0f,
        -50.0f, -50.0f, -50.0f,
        -50.0f,  50.0f, -50.0f,
        -50.0f,  50.0f, -50.0f,
        -50.0f,  50.0f,  50.0f,
        -50.0f, -50.0f,  50.0f,

        50.0f, -50.0f, -50.0f,
        50.0f, -50.0f,  50.0f,
        50.0f,  50.0f,  50.0f,
        50.0f,  50.0f,  50.0f,
        50.0f,  50.0f, -50.0f,
        50.0f, -50.0f, -50.0f,

        -50.0f, -50.0f,  50.0f,
        -50.0f,  50.0f,  50.0f,
        50.0f,  50.0f,  50.0f,
        50.0f,  50.0f,  50.0f,
        50.0f, -50.0f,  50.0f,
        -50.0f, -50.0f,  50.0f,

        -50.0f,  50.0f, -50.0f,
        50.0f,  50.0f, -50.0f,
        50.0f,  50.0f,  50.0f,
        50.0f,  50.0f,  50.0f,
        -50.0f,  50.0f,  50.0f,
        -50.0f,  50.0f, -50.0f,

        -50.0f, -50.0f, -50.0f,
        -50.0f, -50.0f,  50.0f,
        50.0f, -50.0f, -50.0f,
        50.0f, -50.0f, -50.0f,
        -50.0f, -50.0f,  50.0f,
        50.0f, -50.0f,  50.0f
    };

    glGenVertexArrays(1, &VAO);
	// Creates on GPU the vertex buffer object
	glGenBuffers(1, &VBO);
	// Binds the vertex array to set all the its properties
	glBindVertexArray(VAO);

	// Sets the buffer geometry data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);

	glBindVertexArray(0);

    textureId = loadCubemap(faces);
    
    shader = new Shader("assets/shaders/cubeMap.vert", "assets/shaders/cubeMap.frag");
}

CubeMap::~CubeMap()
{
    glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
    delete shader;
}

void CubeMap::Draw(DrawParameters drawParameters){

    shader->use();
    shader->setMat4("view", drawParameters.view);
    shader->setVec3("viewPos", drawParameters.viewPos);
    shader->setMat4("projection", drawParameters.projection);

    //glDepthMask(GL_FALSE);

    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //glDepthMask(GL_TRUE);

	glBindVertexArray(0);
}