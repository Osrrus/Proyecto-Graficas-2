#include "Model.h"

Model::Model(std::vector<glm::vec3> Vertices, std::vector<glm::vec2> TextCoord, std::vector<glm::vec3> normalCoord, std::vector<glm::vec3> tangent, std::vector<glm::vec3> bitangent, char id[], std::string shaderUsed)
{
	this->visible = true;
	this->verticesSize = Vertices.size();
	this->id.assign(id);
	std::cout << id << std::endl;
	primero = true;
	glGenVertexArrays(1, &VAO);
	// Creates on GPU the vertex buffer object
	glGenBuffers(5, VBO);
	// Binds the vertex array to set all the its properties
	glBindVertexArray(VAO);

	// Sets the buffer geometry data
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(glm::vec3), &Vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);

	// text Coord
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, TextCoord.size() * sizeof(glm::vec2), &TextCoord[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *)0);

	// normals
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, normalCoord.size() * sizeof(glm::vec3), &normalCoord[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);

	//tangent
	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, tangent.size() * sizeof(glm::vec3), &tangent[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);

	//bitangent
	glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
	glBufferData(GL_ARRAY_BUFFER, bitangent.size() * sizeof(glm::vec3), &bitangent[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);

	glBindVertexArray(0);

	loadShader(shaderUsed);
}

Model::~Model()
{
	delete shader;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(5, VBO);
}

void Model::loadShader(std::string useShader)
{

	if (useShader == "reflect")
	{

		shader = new Shader("assets/shaders/basic.vert", "assets/shaders/reflect.frag");
	}
	else if (useShader == "CT")
	{

		shader = new Shader("assets/shaders/basic.vert", "assets/shaders/basic.frag");
	}
	else if(useShader == "Parallax"){

		shader = new Shader("assets/shaders/basic.vert", "assets/shaders/parallax.frag");
	}
	else if (useShader == "OcclusionParallax") {

		shader = new Shader("assets/shaders/basic.vert", "assets/shaders/occlusionParallax.frag");
	}
	else if(useShader == "Transparent"){

		shader = new Shader("assets/shaders/basic.vert", "assets/shaders/transparent.frag");

	}
	else
	{
		shader = new Shader("assets/shaders/basic.vert", "assets/shaders/basic.frag");
	}

	//nameShader = useShader;
	shader->use();
}

void Model::Draw(DrawParameters drawParameters)
{

	// Binds the vertex array to be drawn
	unsigned int textureSetoff = textureIds.size();
	
	for (unsigned int i = 0; i < textureIds.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		glUniform1i(glGetUniformLocation(shader->ID, ("texture_" + textureIds[i].name).c_str()), i);

		glBindTexture(GL_TEXTURE_2D, textureIds[i].id);
	}

	glActiveTexture(GL_TEXTURE0 + textureSetoff);
	glUniform1i(glGetUniformLocation(shader->ID, "texture_deepth"), textureSetoff);

	glBindTexture(GL_TEXTURE_2D, drawParameters.deepTexture);

	shader->setVec3("modelMaterial_a", material.aMaterial);
	shader->setVec3("modelMaterial_d", material.dMaterial);
	shader->setVec3("modelMaterial_s", material.sMaterial);
	shader->setFloat("modelMaterial_ns", material.nsMaterial);
	shader->setFloat("modelMaterial_r", material.rMaterial);
	shader->setBool("refra", material.refra);
	shader->setFloat("refractive", material.refractive);

	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO);
	// Renders the triangle gemotry
	if (visible)
		glDrawArrays(GL_TRIANGLES, 0, verticesSize);

	glBindVertexArray(0);
}

void Model::addTexture(Texture a)
{

	textureIds.push_back(a);
}