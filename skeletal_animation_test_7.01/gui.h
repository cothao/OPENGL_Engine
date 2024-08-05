#ifndef GUI_H
#define GUI_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "engine.h"

class Gui
{
public:

	float Position[3]	=	{1.,1.,1.};
	float Color[3]		=	{1.,1.,1.};

	Gui();

	virtual void initGui(Engine engine);
	virtual void displayGui(Engine& engine, bool editMode);
	virtual void newGuiFrame();

};

#endif
