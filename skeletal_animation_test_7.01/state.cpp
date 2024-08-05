#include "state.h"
#include "iostream"

State::State()
{

};

State* State::Input(Event event)
{
	return new State();
};

void State::Update(float Delta, Player* player)
{

};