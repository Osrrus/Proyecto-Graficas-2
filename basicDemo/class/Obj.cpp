#include "Obj.h"

Obj::Obj()
{
    this->model = glm::mat4(1.0f);
}

Obj::~Obj()
{
    for(int i = 0; i < models.size(); i++){
        delete models[i];
    }
}

void Obj::Draw(DrawParameters drawParameters){

    for(int i = 0; i < models.size(); i++){

        models[i]->shader->use();
        models[i]->shader->setMat4("view", drawParameters.view);
        models[i]->shader->setVec3("viewPos", drawParameters.viewPos);
        models[i]->shader->setMat4("projection", drawParameters.projection);
        models[i]->shader->setMat4("model", model);

		glBindTexture(GL_TEXTURE_CUBE_MAP, drawParameters.skyboxTexture);  

		drawParameters.dirLigth->setLight(models[i]->shader);

        models[i]->Draw();
    }
}

void Obj::addModel(Model* M){

    models.push_back(M);
}