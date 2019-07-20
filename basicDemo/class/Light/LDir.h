#pragma once
#include "Light.h"
#include "../Shader.h"

class DirLigth : public Light
{
public:

	glm::vec3 direccion;
	DirLigth(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
	~DirLigth();
	void setLight(Shader*);
private:

};

