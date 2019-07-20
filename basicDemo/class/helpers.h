#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "Light/LDir.h"
#include <iostream>

struct MaterialColor {

		glm::vec3 aMaterial;
		glm::vec3 dMaterial;
		glm::vec3 sMaterial;
		float nsMaterial;
		float rMaterial;
		float refractive;
		bool refra;
};

struct Texture
{
	unsigned int id;
	std::string name;
};

struct DrawParameters
{
	glm::mat4 view;
	glm::vec3 viewPos;
	glm::mat4 projection;
	unsigned int skyboxTexture;
	DirLigth* dirLigth;
	
};
