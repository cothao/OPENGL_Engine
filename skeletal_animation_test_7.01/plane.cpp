#include "plane.h"
#include "shader.h"

Plane::Plane(const Shader shader)
{
	this->shader = shader;
	this->initData();
};

void Plane::initData()
{
    
    float square[] = {
        // positions          // normals         
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    };
    
    unsigned int VBO;

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    this->shader.use();

}

void Plane::render(glm::mat4 projection, glm::mat4 view, glm::vec3 scale, glm::vec3 translate, float rotate, glm::vec3 rotateDir, glm::vec3 color, glm::vec3 lightPos, glm::vec3 cameraPos)
{

    this->lightPos = lightPos;

    glBindVertexArray(this->VAO);

    this->shader.use();
    
    glm::mat4 model = glm::mat4(1.0);

    this->shader.setVec3("viewPos", cameraPos.x, cameraPos.y, cameraPos.z);

    this->shader.setMat4("view", view);
    this->shader.setMat4("projection", projection);

    model = glm::translate(model, translate);

    model = glm::rotate(model, glm::radians(rotate), rotateDir);

    model = glm::scale(model, scale);

    this->shader.setMat4("model", model);
    this->shader.setVec3("lightPos", this->lightPos.x, this->lightPos.y, this->lightPos.z);

    this->shader.setVec3("color", color.r, color.g, color.b);
    this->shader.setVec3("lightColor", 1., 1., 1.);


    glDrawArrays(GL_TRIANGLES, 0, 6);

}
