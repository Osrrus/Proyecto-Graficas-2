#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <vector>
#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "../Shader.h"
#include "helpers.h"

class Model
{
    private:
        unsigned int VAO;
        unsigned int VBO[5];
        int verticesSize;
        bool primero;
    public:
        MaterialColor material;
        std::vector<Texture> textureIds;
        std::string id;
        Shader *shader;
        bool visible;
		Model(std::vector<glm::vec3> Vertices, std::vector<glm::vec2> TextCoord, std::vector<glm::vec3> normalCoord, std::vector<glm::vec3>,std::vector<glm::vec3>,char id[], std::string shaderUsed);
		~Model();
        void Draw();
        void loadShader(std::string);
        void addTexture(Texture);
};

