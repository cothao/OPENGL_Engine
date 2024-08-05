#ifndef CUBE_H
#define CUBE_H
#include <glm/glm.hpp>
#include "shader.h"
#include "game_object.h"
#include <vector>

class Cube: public GameObject
{
public:

	Shader				shader;
	unsigned int		VAO;
	static inline int	id_generator{ 0 };
	int					ID{};
	float				RotateX = 0.0;
	float				RotateY = 0.0;
	float				RotateZ = 0.0;
	glm::vec3			lightPos;
	glm::vec3			Scale;
	glm::vec3			Position;
	glm::vec3			RotateDirX = glm::vec3(1., 0., 0.);
	glm::vec3			RotateDirY = glm::vec3(0., 1., 0.);
	glm::vec3			RotateDirZ = glm::vec3(0.,0.,1.);
	glm::vec3			Color;
	std::string			Type = "cube";

	Cube(const Shader& shader,
		glm::vec3 scale,
		glm::vec3 position,
		glm::vec3 color
        );

	virtual void initData();
	virtual void setLightPos(glm::vec3 lightPos);
	virtual void render
	(
		glm::mat4 projection, 
		glm::mat4 view, 
		glm::vec3 cameraPos,
		glm::vec3 lightPos
	);
};


#endif // !CUBE_H
