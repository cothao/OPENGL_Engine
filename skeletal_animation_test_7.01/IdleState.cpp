#include "IdleState.h"
#include "iostream"
#include "player.h"

IdleState::IdleState()
{
    std::cout << "Current State: Idle" << "\n";
};

State* IdleState::Input(Event event)
{

    switch (event)
    {
    case EFORWARD:
        std::cout << "Entering Walk..." << "\n";
        return new WalkState();
        break;
    };

};

void IdleState::Update(float Delta, Player* player)
{

}