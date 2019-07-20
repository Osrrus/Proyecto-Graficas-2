#pragma once
#include <glm/glm.hpp>
#include <iostream>

class Light
{
public:
	Light();
	~Light();
	bool active;
	glm::vec3 aColor;
	glm::vec3 dColor;
	glm::vec3 sColor;
	virtual void setLight();
	
private:

};