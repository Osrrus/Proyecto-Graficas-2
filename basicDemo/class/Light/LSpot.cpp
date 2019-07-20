#include "LSpot.h"


SpotLight::SpotLight(glm::vec3 colorAmbiente, glm::vec3 colorDifuso, glm::vec3 colorSpecular, glm::vec3 direccion, glm::vec3 position, float cons, float liner, float quad, float cutoff, float outercut)
{

	this->aColor = colorAmbiente;
	this->dColor = colorDifuso;
	this->sColor = colorSpecular;
	this->direction = direccion;
	this->position = position;
	this->constant = cons;
	this->linear = liner;
	this->quadratic = quad;
	this->cutOff = cutoff;
	this->outerCutOff = outercut;
	this->active = true;

}

void SpotLight::setLight(Shader* shader)
{
	if (active) {

		shader->setVec3("spotLight.position", position);
		shader->setVec3("spotLight.direction", direction);
		shader->setVec3("spotLight.ambient", aColor);
		shader->setVec3("spotLight.diffuse", dColor);
		shader->setVec3("spotLight.specular", sColor);
		shader->setFloat("spotLight.constant", constant);
		shader->setFloat("spotLight.linear", linear);
		shader->setFloat("spotLight.quadratic", quadratic);
		shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(cutOff)));
		shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(outerCutOff)));

	}
	else {

		shader->setVec3("spotLight.position", position);
		shader->setVec3("spotLight.direction", direction);
		shader->setVec3("spotLight.ambient", glm::vec3(0.0f));
		shader->setVec3("spotLight.diffuse", glm::vec3(0.0f));
		shader->setVec3("spotLight.specular", glm::vec3(0.0f));
		shader->setFloat("spotLight.constant", constant);
		shader->setFloat("spotLight.linear", linear);
		shader->setFloat("spotLight.quadratic", quadratic);
		shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(cutOff)));
		shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(outerCutOff)));

	}
}

void SpotLight::setLight(Shader* shader, glm::vec3 cameraPos, glm::vec3 cameraView)
{
	if (this->active) {

		shader->setVec3("spotLight.position", cameraPos);
		shader->setVec3("spotLight.direction", cameraView);
		shader->setVec3("spotLight.ambient", aColor);
		shader->setVec3("spotLight.diffuse", dColor);
		shader->setVec3("spotLight.specular", sColor);
		shader->setFloat("spotLight.constant", constant);
		shader->setFloat("spotLight.linear", linear);
		shader->setFloat("spotLight.quadratic", quadratic);
		shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(cutOff)));
		shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(outerCutOff)));
	}
	else {

		shader->setVec3("spotLight.position", position);
		shader->setVec3("spotLight.direction", direction);
		shader->setVec3("spotLight.ambient", glm::vec3(0.0f));
		shader->setVec3("spotLight.diffuse", glm::vec3(0.0f));
		shader->setVec3("spotLight.specular", glm::vec3(0.0f));
		shader->setFloat("spotLight.constant", constant);
		shader->setFloat("spotLight.linear", linear);
		shader->setFloat("spotLight.quadratic", quadratic);
		shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(cutOff)));
		shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(outerCutOff)));

	}
}

SpotLight::~SpotLight()
{

}
