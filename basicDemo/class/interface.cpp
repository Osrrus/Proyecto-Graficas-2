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