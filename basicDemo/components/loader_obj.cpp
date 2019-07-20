#pragma once
#include "../class/Model.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include "loader.h"

int findModel(std::string a, Obj *obj)
{
	for (int i = 0; i < obj->models.size(); i++)
	{
		if (obj->models[i]->id == a)
		{
			return i;
		}
	}

	return 0;
}

unsigned int loadT(const char *path)
{
	// std::cout << "path :: "<< path << std::endl;
	unsigned int id;
	// Creates the texture on GPU
	glGenTextures(1, &id);
	// Loads the texture
	int textureWidth, textureHeight, numberOfChannels;
	// Flips the texture when loads it because in opengl the texture coordinates are flipped
	stbi_set_flip_vertically_on_load(true);
	// Loads the texture file data
	unsigned char *data = stbi_load(path, &textureWidth, &textureHeight, &numberOfChannels, 0);
	if (data)
	{
		// Gets the texture channel format
		GLenum format;
		GLenum extraFormat;
		switch (numberOfChannels)
		{
		case 1:
			format = GL_RED;
			extraFormat = GL_RED;
			break;
		case 3:
			format = GL_RGB;
			extraFormat = GL_SRGB;
			break;
		case 4:
			format = GL_RGBA;
			extraFormat = GL_SRGB_ALPHA;

			break;
		}

		// Binds the texture
		glBindTexture(GL_TEXTURE_2D, id);
		// Creates the texture
		glTexImage2D(GL_TEXTURE_2D, 0, extraFormat, textureWidth, textureHeight, 0, format, GL_UNSIGNED_BYTE, data);
		// Creates the texture mipmaps
		glGenerateMipmap(GL_TEXTURE_2D);

		// Set the filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "ERROR:: Unable to load texture " << path << std::endl;
		glDeleteTextures(1, &id);
	}
	// We dont need the data texture anymore because is loaded on the GPU
	stbi_image_free(data);

	return id;
}

Obj *loadObj(const char *path,std::string shaderUsed)
{

	FILE *file;
	FILE *mtl;
	Obj *newObj = new Obj();
	Model *newModel;
	int offset = 0;
	int xx;
	bool firtsModel = true;
	char lineActula[128], modelId[64];
	std::string aux, basePath;

	aux.assign(path);
	std::size_t found = aux.rfind("/");
	basePath = aux.substr(0, found + 1);

	if (fopen_s(&file, path, "r") != 0)
	{
		printf("Error al cargar el objeto!\n");
		return NULL;
	}

	while (1)
	{

		fscanf_s(file, "%s", &lineActula);

		if (strcmp(lineActula, "mtllib") == 0)
		{

			fscanf_s(file, "%s", &lineActula);
			aux.assign(lineActula);
			aux = basePath + aux;

			strcpy_s(lineActula, aux.c_str());

			if (fopen_s(&mtl, lineActula, "r") != 0)
			{
				printf("Error al cargar el el MTL!\n");
				return NULL;
			}

			break;
		}
	}

	std::vector<glm::vec3> auxVertices;
	std::vector<glm::vec3> auxNormals;
	std::vector<glm::vec2> auxUvs;

	std::vector<unsigned int> indexVertices;
	std::vector<unsigned int> indexNormals;
	std::vector<unsigned int> indexUvs;

	while (1)
	{
		if (fscanf_s(file, "%s", &lineActula) == EOF)
			break;

		/*if (strcmp(lineActula, "o") == 0) 
		{
			offset += auxVertices.size()-1;
		}*/
		if (strcmp(lineActula, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			auxVertices.push_back(vertex);
		}
		else if (strcmp(lineActula, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			auxUvs.push_back(uv);
		}
		else if (strcmp(lineActula, "vn") == 0)
		{

			glm::vec3 normals;
			fscanf_s(file, "%f %f %f\n", &normals.x, &normals.y, &normals.z);
			auxNormals.push_back(normals);
		}
		else if (strcmp(lineActula, "usemtl") == 0)
		{

			if (firtsModel)
			{

				fscanf_s(file, "%s", &modelId);
				firtsModel = false;
			}
			else
			{

				std::vector<glm::vec3> Vertices;
				std::vector<glm::vec3> Normals;
				std::vector<glm::vec2> Uvs;
				std::vector<glm::vec3> tangent;
				std::vector<glm::vec3> bitangent;


				for (int i = 0; i < indexVertices.size(); i++)
				{

					Vertices.push_back(auxVertices[indexVertices[i]]);
				}

				for (int i = 0; i < indexUvs.size(); i++)
				{

					Uvs.push_back(auxUvs[indexUvs[i]]);
				}

				for (int i = 0; i < indexNormals.size(); i++)
				{

					Normals.push_back(auxNormals[indexNormals[i]]);
				}
				
				glm::vec3 edge1,edge2,auxTangent,auxBitangent;
				glm::vec2 uv1,uv2;

				float delta;

				for (int i = 0; i < Vertices.size(); i+=3)
				{
					
					edge1 = Vertices[i+1] - Vertices[i];
					edge2 = Vertices[i+2] - Vertices[i];

					uv1 = Uvs[i+1] - Uvs[i];
					uv2 = Uvs[i+2] - Uvs[i];
					
					delta = 1.0f/ (uv1.x*uv2.y - uv2.x*uv1.y);
					
					auxTangent.x = delta * (uv2.y * edge1.x - uv1.y * edge2.x); 
					auxTangent.y = delta * (uv2.y * edge1.y - uv1.y * edge2.y);
					auxTangent.z = delta * (uv2.y * edge1.z - uv1.y * edge2.z);

					auxBitangent.x = delta * (-uv2.x * edge1.x - uv1.x * edge2.x);
					auxBitangent.y = delta * (-uv2.x * edge1.y - uv1.x * edge2.y);
					auxBitangent.z = delta * (-uv2.x * edge1.z - uv1.x * edge2.z);

					tangent.push_back(auxTangent);
					tangent.push_back(auxTangent);
					tangent.push_back(auxTangent);

					bitangent.push_back(auxBitangent);
					bitangent.push_back(auxBitangent);
					bitangent.push_back(auxBitangent);


				}

				newModel = new Model(Vertices, Uvs, Normals,tangent,bitangent, modelId, shaderUsed);

				newObj->addModel(newModel);

				fscanf_s(file, "%s", &modelId);

				/*auxVertices.clear();
				auxUvs.clear();
				auxNormals.clear();*/
			}
		}
		else if (strcmp(lineActula, "f") == 0)
		{

			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				printf("Formato no valido\n");
				return NULL;
			}

			indexVertices.push_back(vertexIndex[0] - 1 - offset);
			indexVertices.push_back(vertexIndex[1] - 1 - offset);
			indexVertices.push_back(vertexIndex[2] - 1 - offset);

			indexUvs.push_back(uvIndex[0] - 1 - offset);
			indexUvs.push_back(uvIndex[1] - 1 - offset);
			indexUvs.push_back(uvIndex[2] - 1 - offset);

			indexNormals.push_back(normalIndex[0] - 1 - offset);
			indexNormals.push_back(normalIndex[1] - 1 - offset);
			indexNormals.push_back(normalIndex[2] - 1 - offset);
		}
	}

	std::vector<glm::vec3> Vertices;
	std::vector<glm::vec3> Normals;
	std::vector<glm::vec2> Uvs;
	std::vector<glm::vec3> tangent;
	std::vector<glm::vec3> bitangent;

	for (int i = 0; i < indexVertices.size(); i++)
	{

		Vertices.push_back(auxVertices[indexVertices[i]]);
	}

	for (int i = 0; i < indexUvs.size(); i++)
	{

		Uvs.push_back(auxUvs[indexUvs[i]]);
	}

	for (int i = 0; i < indexNormals.size(); i++)
	{

		Normals.push_back(auxNormals[indexNormals[i]]);
	}

	glm::vec3 edge1, edge2, auxTangent, auxBitangent;
	glm::vec2 uv1, uv2;

	float delta;

	for (int i = 0; i < Vertices.size(); i += 3)
	{

		edge1 = Vertices[i + 1] - Vertices[i];
		edge2 = Vertices[i + 2] - Vertices[i];

		uv1 = Uvs[i + 1] - Uvs[i];
		uv2 = Uvs[i + 2] - Uvs[i];

		delta = 1.0f / (uv1.x * uv2.y - uv2.x * uv1.y);

		auxTangent.x = delta * (uv2.y * edge1.x - uv1.y * edge2.x); 
		auxTangent.y = delta * (uv2.y * edge1.y - uv1.y * edge2.y);
		auxTangent.z = delta * (uv2.y * edge1.z - uv1.y * edge2.z);

		auxBitangent.x = delta * (-uv2.x * edge1.x - uv1.x * edge2.x);
		auxBitangent.y = delta * (-uv2.x * edge1.y - uv1.x * edge2.y);
		auxBitangent.z = delta * (-uv2.x * edge1.z - uv1.x * edge2.z);

		tangent.push_back(auxTangent);
		tangent.push_back(auxTangent);
		tangent.push_back(auxTangent);

		bitangent.push_back(auxBitangent);
		bitangent.push_back(auxBitangent);
		bitangent.push_back(auxBitangent);

	}

	newModel = new Model(Vertices, Uvs, Normals, tangent, bitangent, modelId, shaderUsed);

	newObj->addModel(newModel);
	
	while (1)
	{

		if (fscanf_s(mtl, "%s", &lineActula) == EOF)
			break;

		if (strcmp(lineActula, "Ka") == 0) {

			fscanf_s(mtl, "%f %f %f\n", &newObj->models[xx]->material.aMaterial.x, &newObj->models[xx]->material.aMaterial.y, &newObj->models[xx]->material.aMaterial.z);

		}
		else if (strcmp(lineActula, "Kd") == 0) {
			
			fscanf_s(mtl, "%f %f %f\n", &newObj->models[xx]->material.dMaterial.x, &newObj->models[xx]->material.dMaterial.y, &newObj->models[xx]->material.dMaterial.z);

		}
		else if (strcmp(lineActula, "Ks") == 0) {

			fscanf_s(mtl, "%f %f %f\n", &newObj->models[xx]->material.sMaterial.x, &newObj->models[xx]->material.sMaterial.y, &newObj->models[xx]->material.sMaterial.z);

		}
		else if (strcmp(lineActula, "Ns") == 0) {

			fscanf_s(mtl, "%f\n", &newObj->models[xx]->material.nsMaterial);
		}

		else if (strcmp(lineActula, "newmtl") == 0)
		{

			fscanf_s(mtl, "%s", &lineActula);
			// std::cout << "Hola: " << lineActula << std::endl;
			xx = findModel(lineActula, newObj);
			newObj->models[xx]->material.rMaterial = 0.5;
			newObj->models[xx]->material.refra = 1;
		}
		else if (strcmp(lineActula, "map_Kd") == 0)
		{
			fscanf_s(mtl, "%s", &lineActula);

			aux.assign(lineActula);
			aux = basePath + aux;
			strcpy_s(lineActula, aux.c_str());

			// std::cout <<"Hola: "<<lineActula<<std::endl;
			Texture a;
			a.id = loadT(lineActula);
			// std::cout << a.id<<std::endl;
			a.name = "diffuse";
			newObj->models[xx]->addTexture(a);
		}
		else if (strcmp(lineActula, "map_d") == 0)
		{
			fscanf_s(mtl, "%s", &lineActula);

			aux.assign(lineActula);
			aux = basePath + aux;
			strcpy_s(lineActula, aux.c_str());
			// std::cout << "Hola: " << lineActula << std::endl;
			Texture a;
			a.id = loadT(lineActula);
			a.name = "alpha";
			newObj->models[xx]->addTexture(a);
		}
		else if (strcmp(lineActula, "map_Ns") == 0)
		{
			fscanf_s(mtl, "%s", &lineActula);

			aux.assign(lineActula);
			aux = basePath + aux;
			strcpy_s(lineActula, aux.c_str());

			Texture a;
			a.id = loadT(lineActula);
			a.name = "specularH";
			newObj->models[xx]->addTexture(a);
		}
		else if (strcmp(lineActula, "map_Ks") == 0)
		{
			fscanf_s(mtl, "%s", &lineActula);

			aux.assign(lineActula);
			aux = basePath + aux;
			strcpy_s(lineActula, aux.c_str());

			Texture a;
			a.id = loadT(lineActula);
			a.name = "specular";
			newObj->models[xx]->addTexture(a);
		}
		else if (strcmp(lineActula, "map_Bump") == 0)
		{
			//fscanf_s(mtl, "%s", &lineActula);
			//fscanf_s(mtl, "%s", &lineActula);
			fscanf_s(mtl, "%s", &lineActula);

			aux.assign(lineActula);
			aux = basePath + aux;
			strcpy_s(lineActula, aux.c_str());
			
			Texture a;
			a.id = loadT(lineActula);
			a.name = "normals";
			newObj->models[xx]->addTexture(a);
		}
	}

	fclose(file);
	fclose(mtl);
	//unsigned int textureID = loadT(texturePath);

	return newObj;
}