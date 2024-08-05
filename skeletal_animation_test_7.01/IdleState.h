#ifndef IDLESTATE_H
#define IDLESTATE_H
#include "state.h"
#include "WalkState.h"


class IdleState : public State
{
public:
	IdleState();
	std::string st = "Idle";

	virtual State* Input(Event event);
	virtual void Update(float Delta, Player* player);
};

#endif // !IDLESTATE_H
