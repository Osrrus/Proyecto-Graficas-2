#include "LPoint.h"

PointLight::PointLight(glm::vec3 colorAmbiente, glm::vec3 colorDifuso, glm::vec3 colorSpecular, glm::vec3 direccion, float cons, float liner, float quad, int id, int modelId)
{

	this->aColor = colorAmbiente;
	this->dColor = colorDifuso;
	this->sColor = colorSpecular;
	this->position = direccion;
	this->constant = cons;
	this->linear = liner;
	this->quadratic = quad;
	this->active = true;
	this->id = id + '0';
	this->name = "pointLight[";
	this->name = name + this->id + "]" ;
	this->modelId = modelId;

}

PointLight::~PointLight()
{
}

void PointLight::setLight(Shader* shader)
{
	if (this->active) {

		shader->setVec3(name + ".ambient", aColor);
		shader->setVec3(name + ".diffuse", dColor);
		shader->setVec3(name + ".specular", sColor);
		shader->setVec3(name + ".position", position);
		shader->setFloat(name + ".constant", constant);
		shader->setFloat(name + ".linear", linear);
		shader->setFloat(name + ".quadratic", quadratic);
	}
	else {

		shader->setVec3(name + ".ambient", glm::vec3(0.0f));
		shader->setVec3(name + ".diffuse", glm::vec3(0.0f));
		shader->setVec3(name + ".specular", glm::vec3(0.0f));
		shader->setVec3(name + ".position", glm::vec3(0.0f, 1.0f, -5.0f));
		shader->setFloat(name + ".constant", 0.5f);
		shader->setFloat(name + ".linear", 0.2f);
		shader->setFloat(name + ".quadratic", 0.032f);

	}
}

