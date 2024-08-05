#ifndef PLAYER_H
#define PLAYER_H

#include "model.h"
#include "cube.h"
#include <GLFW/glfw3.h>
#include "state.h"
#include "WalkState.h"
#include "IdleState.h"

class Player : virtual public Model
{
public:

	State* ActiveState = new IdleState(); // needs to be a pointer to walk state instead of a ref to State
	bool		Keys[1024];
	bool		IsCollision = false;
	glm::vec3	Direction;
	float		XDiff;
	float		YDiff;
	Player(string const& path, bool flip = true, glm::vec3 pos = glm::vec3(1.0), glm::vec3 scale = glm::vec3(1.0), bool gamma = false);

	Player();

	virtual void handleInput(float DeltaTime, bool& IsEditing);
	virtual void handleMouseInput(float DeltaTime, bool& IsEditing);
	virtual bool handleCollision(Cube cube);
};

#endif PLAYER_H