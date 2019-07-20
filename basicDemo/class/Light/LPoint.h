#pragma once
#include "Light.h"
#include "../Shader.h"
#include "glm/glm.hpp"

class PointLight : public Light
{
public:
	glm::vec3 position;
	float constant, linear, quadratic;
	std::string name;
	char id;
	PointLight(glm::vec3 colorAmbiente, glm::vec3 colorDifuso, glm::vec3 colorSpecular, glm::vec3 direccion, float cons, float liner, float quad, int id, int modelId);
	~PointLight();
	void setLight(Shader *);
	int modelId;
private:

};
