#ifndef STATE_H
#define STATE_H
#include <string>
class Player;

enum Event
{
	EIDLE,
	EFORWARD,
	EBACKWARD,
	ESHOOT,
};

class State
{
public:
	State();
	std::string st = "Null";

	bool							Keys[1024];
	Event		CurrentEvent{ EFORWARD };


	virtual State* Input(Event event);
	virtual void Update(float Delta, Player* player);
};

#endif