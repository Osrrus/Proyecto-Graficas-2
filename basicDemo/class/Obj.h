#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <glm/glm.hpp>
#include "Model.h"
#include "helpers.h"

class Obj
{
    private:
    public:
        glm::mat4 model;
        std::vector<Model*> models;
        Obj();
        ~Obj();
        void addModel(Model*);
        void Draw(DrawParameters);
};


