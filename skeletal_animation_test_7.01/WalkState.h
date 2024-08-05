#ifndef WALKSTATE_H
#define WALKSTATE_H
#include "state.h"
#include <string>
//#include  "GLFW/glfw3.h"

class Player;

class WalkState: public State
{
public:
	WalkState();
	std::string st = "Walk";
	virtual State* Input(Event event);
	virtual void Update(float Delta, Player* player);

};

#endif