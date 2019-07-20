#include "LDir.h"

DirLigth::DirLigth(glm::vec3 colorAmbiente, glm::vec3 colorDifuso, glm::vec3 colorSpecular, glm::vec3 direccion)
{
	this->aColor = colorAmbiente;
	this->dColor = colorDifuso;
	this->sColor = colorSpecular;
	this->direccion = direccion;
	this->active = true;
}

DirLigth::~DirLigth()
{
}

void DirLigth::setLight(Shader *shader) {
	
	if (active) {

		shader->setVec3("dirLight.ambient", aColor);
		shader->setVec3("dirLight.diffuse", dColor);
		shader->setVec3("dirLight.specular", sColor);
		shader->setVec3("dirLight.direction", direccion);

	}
	else {

		shader->setVec3("dirLight.ambient", glm::vec3(0.0f));
		shader->setVec3("dirLight.diffuse", glm::vec3(0.0f));
		shader->setVec3("dirLight.specular", glm::vec3(0.0f));
		shader->setVec3("dirLight.direction", direccion);
	}
}