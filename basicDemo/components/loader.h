#pragma once
#include "../class/Obj.h"
#include <iostream>

Obj* loadObj(const char* path,std::string shaderUsed);
unsigned int loadCubemap(std::vector<std::string> faces);
unsigned int loadT(const char *path);