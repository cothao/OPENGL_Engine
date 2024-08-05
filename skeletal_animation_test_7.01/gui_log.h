#ifndef GUI_LOG_H
#define GUI_LOG_H
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "engine.h"
#include "gui.h"
#include <vector>

std::vector<std::string> logs;


//class DisplayLog
//{
//public:
//	std::vector<std::string> log;
//	DisplayLog();
//};

void displayLog(bool editMode, Engine engine)
{

	//DisplayLog log = DisplayLog();

	if (editMode)
	{
	if (ImGui::Begin("Log", NULL, ImGuiWindowFlags_NoCollapse))
	{

		for (std::string log: logs)
		{
			ImGui::Text(log.c_str());
		}

		for (std::string log : engine.logs)
		{
			ImGui::Text(log.c_str());
		}

		ImGui::End();
	}

	}

}

#endif // !GUI_LOG_H
