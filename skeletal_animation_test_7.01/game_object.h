#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm/glm.hpp>
#include "shader.h"

class GameObject
{
public:
	glm::vec3 Position;
	glm::vec3 Size;
	glm::vec3 Color;
	glm::vec3 Rotate;
	glm::vec3 Translate;
	Shader shader;
	std::string type;
	unsigned int VAO;

	GameObject();
	virtual void initData();
	virtual void render
	(
		glm::mat4 projection,
		glm::mat4 view,
		glm::vec3 scale,
		glm::vec3 translate,
		float rotate,
		glm::vec3 rotateDir,
		glm::vec3 color,
		glm::vec3 lightPos,
		glm::vec3 cameraPos
	);

};

#endif // !GAME_OBJECT_H
