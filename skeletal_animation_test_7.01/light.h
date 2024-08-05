#ifndef LIGHT_H
#define LIGHT_H
#include <glm/glm.hpp>
#include "game_object.h"
#include "shader.h"

class Light: public GameObject
{
public:

	Shader shader;
	unsigned int VAO;
	glm::vec3 pos;
	std::string type = "light";

	Light(const Shader& shader, glm::vec3 lightPos);
	virtual void initData();
	virtual void render(glm::mat4 projection, glm::mat4 view, glm::vec3 scale, glm::vec3 translate, float rotate, glm::vec3 rotateDir, glm::vec3 color);
};


#endif // !CUBE_H
