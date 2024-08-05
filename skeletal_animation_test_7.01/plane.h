#ifndef PLANE
#define PLANE

#include "shader.h"
#include "game_object.h"

class Plane: public GameObject
{
public:

	Shader shader;
	unsigned int VAO;
	glm::vec3 lightPos;
	std::string type = "plane";

	Plane(const Shader shader);

	// This will initialize the VAO, VBO, and shader
	virtual void initData();
	virtual void render(glm::mat4 projection, glm::mat4 view, glm::vec3 scale, glm::vec3 translate, float rotate, glm::vec3 rotateDir, glm::vec3 color, glm::vec3 lightPos, glm::vec3 cameraPos);

};

#endif // !PLANE
