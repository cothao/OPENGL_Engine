#ifndef GUI_OBJECTS_H
#define GUI_OBJECTS_H
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "engine.h"
#include "gui.h"

void displayObjectsInterface(Engine& engine, bool editMode,Gui& gui)
{

    if (editMode)
    {


        if (ImGui::Begin("Hello world"))
        {

            if (ImGui::BeginTabBar("MenuItems"))
            {

                if (ImGui::BeginTabItem("Create Model"))
                {



                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Create Object"))
                {
                    if (ImGui::BeginTabBar("Create Object"))
                    {
                        const char* items[] = { "Cube", "Light", "Plane" };
                        static const char* current_item = "Cube";

                        if (ImGui::BeginCombo(current_item, *items))
                        {
                            for (int i = 0; i < IM_ARRAYSIZE(items); i++)
                            {
                                bool is_selected = (current_item == items[i]);
                                if (ImGui::Selectable(items[i], is_selected))
                                {
                                    current_item = items[i];
                                }
                                if (is_selected)
                                {
                                    ImGui::SetItemDefaultFocus();
                                }
                            }
                            ImGui::EndCombo();
                        }


                        ImGui::InputFloat3("Position", gui.Position);
                        ImGui::ColorEdit3("Color", gui.Color);

                        if (ImGui::Button("Create"))
                        {
                            if (current_item == "Cube")
                            {
                                Shader pShader("./pShader.vs", "./pShader.fs");
                                engine.cubes.push_back(*new Cube(pShader, glm::vec3(1.0), glm::vec3(gui.Position[0], gui.Position[1], gui.Position[2]), glm::vec3(gui.Color[0], gui.Color[1], gui.Color[2])));
                            }
                        }

                        ImGui::EndTabBar();
                    }
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Objects"))
                {
                    if (ImGui::BeginTabBar("Objects"))
                    {
                        if (ImGui::BeginTabItem("Cube"))
                        {

                            for (Cube& cube : engine.cubes)
                            {
                                std::string label = "Cube##" + std::to_string(cube.ID);
                                std::string labelX = "X##" + std::to_string(cube.ID);
                                std::string labelY = "Y##" + std::to_string(cube.ID);
                                std::string labelZ = "Z##" + std::to_string(cube.ID);
                                std::string cubeNo = "Cube##" + std::to_string(cube.ID);
                                std::string labelX_Angle = "X_Angle##" + std::to_string(cube.ID);
                                std::string labelY_Angle = "Y_Angle##" + std::to_string(cube.ID);
                                std::string labelZ_Angle = "Z_Angle##" + std::to_string(cube.ID);
                                std::string button = "Reset Rotation##" + std::to_string(cube.ID);
                                if (ImGui::TreeNode(label.c_str()))
                                {


                                    ImGui::Text(cubeNo.c_str());
                                    ImGui::Text("Position");
                                    ImGui::InputFloat(labelX.c_str(), &cube.Position.x);
                                    ImGui::InputFloat(labelY.c_str(), &cube.Position.y);
                                    ImGui::InputFloat(labelZ.c_str(), &cube.Position.z);
                                    ImGui::Text("Rotation");
                                    ImGui::SliderAngle(labelX_Angle.c_str(), &cube.RotateX);
                                    ImGui::SliderAngle(labelY_Angle.c_str(), &cube.RotateY);
                                    ImGui::SliderAngle(labelZ_Angle.c_str(), &cube.RotateZ);

                                    if (ImGui::Button(button.c_str()))
                                    {
                                        cube.RotateX = 0.0;
                                        cube.RotateY = 0.0;
                                        cube.RotateZ = 0.0;
                                    }
                                    ImGui::TreePop();
                                }
                                ImGui::Separator();
                            }

                            ImGui::EndTabItem();
                        }

                        if (ImGui::BeginTabItem("Lights"))
                        {

                            ImGui::EndTabItem();
                        }

                        if (ImGui::BeginTabItem("Planes"))
                        {

                            ImGui::EndTabItem();
                        }

                        if (ImGui::BeginTabItem("Models"))
                        {
                            for (Model& model : engine.models)
                            {
                                std::string label = "Model##" + std::to_string(model.ID);
                                std::string labelX = "X##" + std::to_string(model.ID);
                                std::string labelY = "Y##" + std::to_string(model.ID);
                                std::string labelZ = "Z##" + std::to_string(model.ID);
                                std::string modelNo = "Model##" + std::to_string(model.ID);
                                std::string labelX_Angle = "X_Angle##" + std::to_string(model.ID);
                                std::string labelY_Angle = "Y_Angle##" + std::to_string(model.ID);
                                std::string labelZ_Angle = "Z_Angle##" + std::to_string(model.ID);
                                std::string button = "Reset Rotation##" + std::to_string(model.ID);
                                if (ImGui::TreeNode(label.c_str()))
                                {


                                    ImGui::Text(modelNo.c_str());
                                    ImGui::Text("Position");
                                    ImGui::InputFloat(labelX.c_str(), &model.Position.x);
                                    ImGui::InputFloat(labelY.c_str(), &model.Position.y);
                                    ImGui::InputFloat(labelZ.c_str(), &model.Position.z);
                                    ImGui::Text("Rotation");
                                    ImGui::SliderAngle(labelX_Angle.c_str(), &model.RotateX);
                                    ImGui::SliderAngle(labelY_Angle.c_str(), &model.RotateY);
                                    ImGui::SliderAngle(labelZ_Angle.c_str(), &model.RotateZ);

                                    if (ImGui::Button(button.c_str()))
                                    {
                                        model.RotateX = 0.0;
                                        model.RotateY = 0.0;
                                        model.RotateZ = 0.0;
                                    }
                                    ImGui::TreePop();
                                }
                                ImGui::Separator();
                            }

                            ImGui::EndTabItem();
                        }

                        ImGui::EndTabBar();
                    }
                    ImGui::EndTabItem();

                }

                ImGui::EndTabBar();
            }
        }
        ImGui::End();
    }
    ImGui::Render();
}

#endif // !GUI_OBJECTS_H
