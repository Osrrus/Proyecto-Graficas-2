#pragma once
#include "Light.h"
#include <glm/glm.hpp>
#include "../Shader.h"

class SpotLight : public Light
{
public:
	glm::vec3 position, direction;
	float constant, linear, quadratic, cutOff, outerCutOff;
	SpotLight(glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3, float, float, float, float,float);
	void setLight(Shader* shader);
	void setLight(Shader* shader, glm::vec3 cameraPos, glm::vec3 cameraView);
	~SpotLight();

private:

};
