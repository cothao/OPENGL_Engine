#include "gui.h"
#include "shader.h"
#include "gui_objects.h"
#include "gui_log.h"

Gui::Gui()
{

}

void Gui::displayGui(Engine& engine, bool editMode)
{

    displayLog(editMode, engine);
    displayObjectsInterface(engine, editMode, *this);

}

void Gui::initGui(Engine engine)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(engine.window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Gui::newGuiFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}