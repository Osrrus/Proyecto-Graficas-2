#include "interface.h"

TwInterface::TwInterface(unsigned int Width, unsigned int Height,std::string typeMenu){

	TwInit(TW_OPENGL_CORE, NULL);
	menus[typeMenu] = TwNewBar(typeMenu.c_str());
	TwWindowSize(Width, Height);
	TwDefine("dirL color='0 95 25' ");
	TwDefine("dirL text=dark ");
	TwDefine("dirL size='260 260' ");
	TwDefine("dirL refresh=0.001 ");

	if(typeMenu == "dirL"){

		buildDirMenu(typeMenu);

	}
	else if(typeMenu == "Obj"){

		buildDirMenu(typeMenu);

	}

}

void TwInterface::addMenu(unsigned int Width, unsigned int Height,std::string typeMenu){

	TwInit(TW_OPENGL_CORE, NULL);
	menus[typeMenu] = TwNewBar(typeMenu.c_str());
	TwWindowSize(Width, Height);
	TwDefine("Obj color='0 95 25' ");
	TwDefine("Obj text=dark ");
	TwDefine("Obj size='260 260' ");
	TwDefine("Obj refresh=0.001 ");

	if(typeMenu == "dirL"){

		buildDirMenu(typeMenu);

	}
	else if(typeMenu == "Obj"){

		buildObjMenu(typeMenu);

	}

}

void TwInterface::buildDirMenu(std::string typeMenu){

	TwAddVarRW(menus[typeMenu], "dirlVis", TW_TYPE_BOOL8, &dirlVis, " label='Visibilidad'");
	TwAddVarRW(menus[typeMenu], "dirlAmbient", TW_TYPE_COLOR3F, &dirlAmbient, " label='Ambient' group='dirlColor'");
	TwAddVarRW(menus[typeMenu], "dirlDifuse", TW_TYPE_COLOR3F, &dirlDifuse, " label='Difuse'  group='dirlColor'");
	TwAddVarRW(menus[typeMenu], "dirlSpecular", TW_TYPE_COLOR3F, &dirlSpecular, " label='Specular'  group='dirlColor'");
	TwDefine("dirL/dirlColor label='Color'");
	TwAddVarRW(menus[typeMenu], "LightDir", TW_TYPE_DIR3F, &dirlPosition," label='Direccion' ");
	TwDefine("dirL/dirl label='Luz Direccional'");

}

void TwInterface::buildObjMenu(std::string typeMenu){
	
	TwEnumVal DeployType[] = { { Cook_Torrence, "Cook Torrence" },{ Refract_Reflect, "Refract/Reflect" },{ Occlusion_Parallax, "OcclusionParallax" },{ Parallax, "Parallax" } };
	TwType DeployTwType = TwDefineEnum("a", DeployType, 4);

	TwAddVarRW(menus[typeMenu], "Modelo Actual", TW_TYPE_INT32, &modelCon, "min=0");
	TwAddVarRW(menus[typeMenu], "Shader", DeployTwType, &m_shader, "");
	TwAddVarRW(menus[typeMenu], "ModeloVis", TW_TYPE_BOOL8, &modelVis, " label='Visibilidad'");
	TwAddVarRW(menus[typeMenu], "mRefra", TW_TYPE_BOOL8, &refra, " label='Reflect/Refract' step=0.01");
	TwAddVarRW(menus[typeMenu], "mRefractive", TW_TYPE_FLOAT, &refractive, " label='refractive' step=0.01 min='1.0'");
	TwDefine(" Obj/Modelo");

}

std::string TwInterface::getDeployType() {
	if (m_shader == Cook_Torrence) return "CT";
	if (m_shader == Refract_Reflect) return "reflect";
	if (m_shader == Occlusion_Parallax) return "OcclusionParallax";
	if (m_shader == Parallax) return "Parallax";
	return NULL;
}

void TwInterface::setDeployType(std::string a) {

	if (a =="CT")m_shader = Cook_Torrence;
	if (a == "reflect")m_shader = Refract_Reflect;
	if (a == "OcclusionParallax")m_shader = Occlusion_Parallax;
	if (a == "Parallax")m_shader = Parallax;

}