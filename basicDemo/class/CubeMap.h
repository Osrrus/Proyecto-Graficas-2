#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <glm/glm.hpp>
#include "../components/loader.h"
#include "../Shader.h"
#include "./helpers.h"

class CubeMap
{
    private:
        //std::vector<glm::vec3> Vertices;
        unsigned int VAO,VBO;
        Shader *shader;
    public:
        unsigned int textureId;
        CubeMap(std::vector<std::string>);
        ~CubeMap();
        void Draw(DrawParameters);
};

