#include "Windows.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <AntTweakBar.h>
#include <glm/glm.hpp>

typedef enum { Cook_Torrence, Bling_Phong, Refract_Reflect, Occlusion_Parallax, Parallax} SHADER_TYPE;


class TwInterface {

	public : 
		std::map<std::string,TwBar*> menus;
		TwInterface(unsigned int Width, unsigned int Height,std::string);
		std::string getDeployType();
		void addMenu(unsigned int Width, unsigned int Height,std::string typeMenu);
        void buildDirMenu(std::string typeMenu);
		void buildObjMenu(std::string typeMenu);
		void setDeployType(std::string);
		int lightCon, modelCon;
		glm::vec3 mDifuse, mAmbient, mSpecular; 
		float mShinees, pointlShinees, dirlShinees, spotlShinees;
		float pointlConstant, pointlLinear, pointlQuadratic, roughness,refractive;
		float spotlConstant, spotlLinear, spotlQuadratic, spotlcutOff, spotlouterCut;
		glm::vec3 dirlDifuse, dirlAmbient, dirlSpecular;
		glm::vec3 pointlDifuse, pointlAmbient, pointlSpecular;
		glm::vec3 spotlDifuse, spotlAmbient, spotlSpecular;
		glm::vec3 spotlPosition, dirlPosition, pointlPosition;
		glm::vec3 mScale, mPosition;
		glm::vec4 mRotation;
		bool spotlVis, dirlVis, pointlVis, modelVis,refra;
		SHADER_TYPE m_shader;

	private:
};