//#include "renderer.h"
//#include "shader.h"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include "cube.h"
//
//Renderer::Renderer(const Shader& shader, std::string type, const unsigned int& VAO)
//{
//	this->shader = shader;
//    this->VAO = VAO;
//    this->initRenderData(type);
//};
//	
//void Renderer::render(glm::vec3 pos, glm::vec3 size, float rotation, glm::vec3 color)
//{
//
//	this->shader.use();
//
//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::translate(model, glm::vec3(pos));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)
//
//    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
//    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back
//
//    model = glm::scale(model, glm::vec3(size)); // last scale
//
//    this->shader.setMat4("model", model);
//
//
//    // render textured quad
//    this->shader.setVec3("spriteColor", color.r,color.g,color.b);
//
//    glBindVertexArray(this->VAO);
//
//    glDrawArrays(GL_TRIANGLES, 0,36);
//
//};
//
//void Renderer::initRenderData(std::string type)
//{
//
//
//    if (type == "cube")
//    {
//    
//        float vertices[] =
//        {
//            // positions        
//            -0.5f, -0.5f, -0.5f,
//             0.5f, -0.5f, -0.5f,
//             0.5f,  0.5f, -0.5f,
//             0.5f,  0.5f, -0.5f,
//            -0.5f,  0.5f, -0.5f,
//            -0.5f, -0.5f, -0.5f,
//
//            -0.5f, -0.5f,  0.5f,
//             0.5f, -0.5f,  0.5f,
//             0.5f,  0.5f,  0.5f,
//             0.5f,  0.5f,  0.5f,
//            -0.5f,  0.5f,  0.5f,
//            -0.5f, -0.5f,  0.5f,
//
//            -0.5f,  0.5f,  0.5f,
//            -0.5f,  0.5f, -0.5f,
//            -0.5f, -0.5f, -0.5f,
//            -0.5f, -0.5f, -0.5f,
//            -0.5f, -0.5f,  0.5f,
//            -0.5f,  0.5f,  0.5f,
//
//             0.5f,  0.5f,  0.5f,
//             0.5f,  0.5f, -0.5f,
//             0.5f, -0.5f, -0.5f,
//             0.5f, -0.5f, -0.5f,
//             0.5f, -0.5f,  0.5f,
//             0.5f,  0.5f,  0.5f,
//
//            -0.5f, -0.5f, -0.5f,
//             0.5f, -0.5f, -0.5f,
//             0.5f, -0.5f,  0.5f,
//             0.5f, -0.5f,  0.5f,
//            -0.5f, -0.5f,  0.5f,
//            -0.5f, -0.5f, -0.5f,
//
//            -0.5f,  0.5f, -0.5f,
//             0.5f,  0.5f, -0.5f,
//             0.5f,  0.5f,  0.5f,
//             0.5f,  0.5f,  0.5f,
//            -0.5f,  0.5f,  0.5f,
//            -0.5f,  0.5f, -0.5f,
//        };
//
//    unsigned int VBO;
//
//    glGenBuffers(1, &VBO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glGenVertexArrays(1, &this->VAO);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//
//    this->shader.use();
//    }
//
//
//}